/*
* DEEPCRAFT Studio 5.3.2330+a1ee73d5c188e5d397df3d61490cb4b98a7f252b
* Copyright © 2023- Imagimob AB, All Rights Reserved.
* 
* Generated at 03/01/2025 03:54:07 UTC. Any changes will be lost.
* 
* Model ID  51f03916-9d8e-4d99-80ca-79f1a73d601d
* 
* Memory    Size                      Efficiency
* Buffers   24 bytes (RAM)            100 %
* State     1648 bytes (RAM)          100 %
* 
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-2
* 
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | fall
* 
* Layer                          Shape           Type       Function
* Scale                          [6]             float      enqueue
*    scale = 0.125
* Sliding Window (data points)   [60,6]          float      dequeue
*    window_shape = [60,6]
*    stride = 60
*    buffer_multiplier = 1
* 
* Exported functions:
* 
* int IMAI_IMU_dequeue(float *restrict data_out)
*    Description: Dequeue features. RET_SUCCESS (0) on success, RET_NODATA (-1) if no data is available, RET_NOMEM (-2) on internal memory error
*    Parameter data_out is Output of size float[60,6].
* 
* int IMAI_IMU_enqueue(const float *restrict data_in)
*    Description: Enqueue features. Returns SUCCESS (0) on success, else RET_NOMEM (-2) when low on memory.
*    Parameter data_in is Input of size float[6].
* 
* void IMAI_IMU_init(void)
*    Description: Initializes buffers to initial state. This function also works as a reset function.
* 
* 
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#ifndef _IMAI_IMU_IMU_MODEL_H_
#define _IMAI_IMU_IMU_MODEL_H_
#ifdef _MSC_VER
#pragma once
#endif

#include <stdint.h>

typedef struct {    
    char *name;
    double TP; // True Positive or Correct Positive Prediction
    double FN; // False Negative or Incorrect Negative Prediction
    double FP; // False Positive or Incorrect Positive Prediction
    double TN; // True Negative or Correct Negative Prediction
    double TPR; // True Positive Rate or Sensitivity, Recall
    double TNR; // True Negative Rate or Specificity, Selectivity
    double PPV; // Positive Predictive Value or Precision
    double NPV; // Negative Predictive Value
    double FNR; // False Negative Rate or Miss Rate
    double FPR; // False Positive Rate or Fall-Out
    double FDR; // False Discovery Rate
    double FOR; // False Omission Rate
    double F1S; // F1 Score
} IMAI_IMU_stats;

/*
* Tensorflow Test Set
* 
* (ACC) Accuracy 99.274 %
* (F1S) F1 Score 99.346 %
* 
* Name of class                                            (unlabelled)             fall
* (TP) True Positive or Correct Positive Prediction               13222               49
* (FN) False Negative or Incorrect Negative Prediction               68               29
* (FP) False Positive or Incorrect Positive Prediction               29               68
* (TN) True Negative or Correct Negative Prediction                  49            13222
* (TPR) True Positive Rate or Sensitivity, Recall               99.49 %          62.82 %
* (TNR) True Negative Rate or Specificity, Selectivity          62.82 %          99.49 %
* (PPV) Positive Predictive Value or Precision                  99.78 %          41.88 %
* (NPV) Negative Predictive Value                               41.88 %          99.78 %
* (FNR) False Negative Rate or Miss Rate                         0.51 %          37.18 %
* (FPR) False Positive Rate or Fall-Out                         37.18 %           0.51 %
* (FDR) False Discovery Rate                                     0.22 %          58.12 %
* (FOR) False Omission Rate                                     58.12 %           0.22 %
* (F1S) F1 Score                                                99.63 %          50.26 %
*/


#define IMAI_IMU_TEST_AVG_ACC 0.9927438659485338 // Accuracy
#define IMAI_IMU_TEST_AVG_F1S 0.9934641481825112 // F1 Score

#define IMAI_IMU_TEST_STATS { \
 {name: "(unlabelled)", TP: 13222, FN: 68, FP: 29, TN: 49, TPR: 0.9948833709556, TNR: 0.6282051282051, PPV: 0.9978114859255, NPV: 0.4188034188034, FNR: 0.0051166290443, FPR: 0.3717948717948, FDR: 0.0021885140744, FOR: 0.5811965811965, F1S: 0.9963452771184, }, \
 {name: "fall", TP: 49, FN: 29, FP: 68, TN: 13222, TPR: 0.6282051282051, TNR: 0.9948833709556, PPV: 0.4188034188034, NPV: 0.9978114859255, FNR: 0.3717948717948, FPR: 0.0051166290443, FDR: 0.5811965811965, FOR: 0.0021885140744, F1S: 0.5025641025641, }, \
}

#ifdef IMAI_IMU_STATS_ENABLED
static const IMAI_IMU_stats IMAI_IMU_test_stats[] = IMAI_IMU_TEST_STATS;
#endif

/*
* Tensorflow Train Set
* 
* (ACC) Accuracy 99.122 %
* (F1S) F1 Score 99.192 %
* 
* Name of class                                            (unlabelled)             fall
* (TP) True Positive or Correct Positive Prediction               31240              156
* (FN) False Negative or Incorrect Negative Prediction              186               92
* (FP) False Positive or Incorrect Positive Prediction               92              186
* (TN) True Negative or Correct Negative Prediction                 156            31240
* (TPR) True Positive Rate or Sensitivity, Recall               99.41 %          62.90 %
* (TNR) True Negative Rate or Specificity, Selectivity          62.90 %          99.41 %
* (PPV) Positive Predictive Value or Precision                  99.71 %          45.61 %
* (NPV) Negative Predictive Value                               45.61 %          99.71 %
* (FNR) False Negative Rate or Miss Rate                         0.59 %          37.10 %
* (FPR) False Positive Rate or Fall-Out                         37.10 %           0.59 %
* (FDR) False Discovery Rate                                     0.29 %          54.39 %
* (FOR) False Omission Rate                                     54.39 %           0.29 %
* (F1S) F1 Score                                                99.56 %          52.88 %
*/


#define IMAI_IMU_TRAIN_AVG_ACC 0.991223085180274 // Accuracy
#define IMAI_IMU_TRAIN_AVG_F1S 0.9919156900343273 // F1 Score

#define IMAI_IMU_TRAIN_STATS { \
 {name: "(unlabelled)", TP: 31240, FN: 186, FP: 92, TN: 156, TPR: 0.9940813339273, TNR: 0.6290322580645, PPV: 0.9970637048385, NPV: 0.4561403508771, FNR: 0.0059186660726, FPR: 0.3709677419354, FDR: 0.0029362951614, FOR: 0.5438596491228, F1S: 0.9955702858599, }, \
 {name: "fall", TP: 156, FN: 92, FP: 186, TN: 31240, TPR: 0.6290322580645, TNR: 0.9940813339273, PPV: 0.4561403508771, NPV: 0.9970637048385, FNR: 0.3709677419354, FPR: 0.0059186660726, FDR: 0.5438596491228, FOR: 0.0029362951614, F1S: 0.5288135593220, }, \
}

#ifdef IMAI_IMU_STATS_ENABLED
static const IMAI_IMU_stats IMAI_IMU_train_stats[] = IMAI_IMU_TRAIN_STATS;
#endif

/*
* Tensorflow Validation Set
* 
* (ACC) Accuracy 99.211 %
* (F1S) F1 Score 99.224 %
* 
* Name of class                                            (unlabelled)             fall
* (TP) True Positive or Correct Positive Prediction               10765               42
* (FN) False Negative or Incorrect Negative Prediction               46               40
* (FP) False Positive or Incorrect Positive Prediction               40               46
* (TN) True Negative or Correct Negative Prediction                  42            10765
* (TPR) True Positive Rate or Sensitivity, Recall               99.57 %          51.22 %
* (TNR) True Negative Rate or Specificity, Selectivity          51.22 %          99.57 %
* (PPV) Positive Predictive Value or Precision                  99.63 %          47.73 %
* (NPV) Negative Predictive Value                               47.73 %          99.63 %
* (FNR) False Negative Rate or Miss Rate                         0.43 %          48.78 %
* (FPR) False Positive Rate or Fall-Out                         48.78 %           0.43 %
* (FDR) False Discovery Rate                                     0.37 %          52.27 %
* (FOR) False Omission Rate                                     52.27 %           0.37 %
* (F1S) F1 Score                                                99.60 %          49.41 %
*/


#define IMAI_IMU_VALIDATION_AVG_ACC 0.9921050215734876 // Accuracy
#define IMAI_IMU_VALIDATION_AVG_F1S 0.9922432490090486 // F1 Score

#define IMAI_IMU_VALIDATION_STATS { \
 {name: "(unlabelled)", TP: 10765, FN: 46, FP: 40, TN: 42, TPR: 0.9957450744611, TNR: 0.5121951219512, PPV: 0.9962980101804, NPV: 0.4772727272727, FNR: 0.0042549255388, FPR: 0.4878048780487, FDR: 0.0037019898195, FOR: 0.5227272727272, F1S: 0.9960214655810, }, \
 {name: "fall", TP: 42, FN: 40, FP: 46, TN: 10765, TPR: 0.5121951219512, TNR: 0.9957450744611, PPV: 0.4772727272727, NPV: 0.9962980101804, FNR: 0.4878048780487, FPR: 0.0042549255388, FDR: 0.5227272727272, FOR: 0.0037019898195, F1S: 0.4941176470588, }, \
}

#ifdef IMAI_IMU_STATS_ENABLED
static const IMAI_IMU_stats IMAI_IMU_validation_stats[] = IMAI_IMU_VALIDATION_STATS;
#endif

#define IMAI_IMU_API_QUEUE

// All symbols in order
#define IMAI_IMU_SYMBOL_MAP {"unlabelled", "fall"}

// Model GUID (16 bytes)
#define IMAI_IMU_MODEL_ID {0x16, 0x39, 0xf0, 0x51, 0x8e, 0x9d, 0x99, 0x4d, 0x80, 0xca, 0x79, 0xf1, 0xa7, 0x3d, 0x60, 0x1d}

// First nibble is bit encoding, second nibble is number of bytes
#define IMAGINET_TYPES_NONE	(0x0)
#define IMAGINET_TYPES_FLOAT32	(0x14)
#define IMAGINET_TYPES_FLOAT64	(0x18)
#define IMAGINET_TYPES_INT8	(0x21)
#define IMAGINET_TYPES_INT16	(0x22)
#define IMAGINET_TYPES_INT32	(0x24)
#define IMAGINET_TYPES_INT64	(0x28)
#define IMAGINET_TYPES_QDYN8	(0x31)
#define IMAGINET_TYPES_QDYN16	(0x32)
#define IMAGINET_TYPES_QDYN32	(0x34)

// data_in [6] (24 bytes)
#define IMAI_IMU_DATA_IN_COUNT (6)
#define IMAI_IMU_DATA_IN_TYPE float
#define IMAI_IMU_DATA_IN_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_IMU_DATA_IN_SCALE (1)
#define IMAI_IMU_DATA_IN_OFFSET (0)
#define IMAI_IMU_DATA_IN_IS_QUANTIZED (0)

// data_out [60,6] (1440 bytes)
#define IMAI_IMU_DATA_OUT_COUNT (360)
#define IMAI_IMU_DATA_OUT_TYPE float
#define IMAI_IMU_DATA_OUT_TYPE_ID IMAGINET_TYPES_FLOAT32
#define IMAI_IMU_DATA_OUT_SCALE (1)
#define IMAI_IMU_DATA_OUT_OFFSET (0)
#define IMAI_IMU_DATA_OUT_IS_QUANTIZED (0)

#define IMAI_IMU_KEY_MAX (4)



// Return codes
#define IMAI_IMU_RET_SUCCESS 0
#define IMAI_IMU_RET_NODATA -1
#define IMAI_IMU_RET_NOMEM -2

// Exported methods
int IMAI_IMU_dequeue(float *restrict data_out);
int IMAI_IMU_enqueue(const float *restrict data_in);
void IMAI_IMU_init(void);

#endif /* _IMAI_IMU_IMU_MODEL_H_ */
