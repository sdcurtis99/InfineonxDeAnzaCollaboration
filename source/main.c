/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for Imagimob_MTBML_Deploy Example.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "stdlib.h"

#include "imu.h"
#include "audio.h"
#include "inference.h"
#include "config.h"

#include "imu_model.h"
#include "pdm_model.h"

/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
cy_rslt_t system_init(void);
/*******************************************************************************
* Global Variables
*******************************************************************************/
volatile bool pdm_pcm_flag;
volatile bool imu_flag;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*
* This is the main function. It sets up the neural net based on the chosen
* Imagimob model (either IMU or PDM based) and sets up the selected sensor.
* Main continuously loops checking if there is enough data to feed the preprocessor
* supplied by Imagimob. When the data processing is completed, the data is
* passed to the model for inferencing and the results are printed to the screen.
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    
    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");

    printf("****************** "
           "Machine Learning: Imagimob MTBML Deploy"
           "****************** \r\n\n");

#if INFERENCE_MODE_SELECT == IMU_INFERENCE
    /* Store the processed data from IMAI_IMU_dequeue */
    float processed_data[IMAI_IMU_DATA_OUT_COUNT];
#else
    /* Store processed data from IMAI_dequeue */
    float processed_data[IMAI_PDM_DATA_OUT_COUNT];
#endif

    /* Initialize inference engine and sensors */
    result = system_init();
    /* Initialization failed */
    if(CY_RSLT_SUCCESS != result)
    {
        /* Reset the system on sensor fail */
        NVIC_SystemReset();
    }

    for (;;)
    {

#if INFERENCE_MODE_SELECT == IMU_INFERENCE
        /* Check if the IMU interrupt has triggered */
        if(true == imu_flag)
        {
            imu_flag = false;

            /* Check if there is enough pre-processed data to start
             * an inference. When there is enough data, processed_data
             * points to the processed IMU data */
            if (IMAI_IMU_RET_SUCCESS == IMAI_IMU_dequeue(processed_data))
            {
                /* Feed the neural net the pre-processed data */
                inference_feed(processed_data);
                inference_output_control();
            }
        }
#endif

#if INFERENCE_MODE_SELECT == PDM_INFERENCE
        /* Check if the PDM event has triggered */
        if(true == pdm_pcm_flag)
        {
            /* Check if there is enough pre-processed data to start
             * an inference. When there is enough data, processed_data
             * points to the processed PDM data */
            if(PDM_PROCESSING_COMPLETE == pdm_preprocessing_feed(processed_data))
            {
                /* Feed the neural net the pre-processed data */
                inference_feed(processed_data);
                inference_output_control();

            }
            /* Reset the pdm event flag */
            pdm_pcm_flag = false;
        }
#endif

    }
}

/*******************************************************************************
* Function Name: system_init
********************************************************************************
* Summary:
*  Initializes the neural network based on the Imagimob model and the
*  Imagimob pre-processor. Initializes the PDM or IMU based on
*  INFERENCE_MODE_SELECT which is set in config.h
*
* Parameters:
*  None
*
* Returns:
*  The status of the initialization.
*
*******************************************************************************/
cy_rslt_t system_init(void)
{
    cy_rslt_t result;

    /* Initialize the inference engine */
    result = inference_init();
    if(CY_RSLT_SUCCESS != result)
    {
        return result;
    }

#if INFERENCE_MODE_SELECT == IMU_INFERENCE
    /* Initialize Imagimob pre-processing library */
    IMAI_IMU_init();
    /* Start the imu, timer, and pre-process the data */
    result = imu_init();
#endif

#if INFERENCE_MODE_SELECT == PDM_INFERENCE
    /* Initialize Imagimob pre-processing library */
    IMAI_PDM_init();
    /* Configure PDM, PDM clocks, and PDM event */
    result = pdm_init();
#endif
    return result;
}

/* [] END OF FILE */
