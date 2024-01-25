/**************************************************************************************************
* Copyright (C) 2019-2021 Maxim Integrated Products, Inc. All Rights Reserved.
*
* Maxim Integrated Products, Inc. Default Copyright Notice:
* https://www.maximintegrated.com/en/aboutus/legal/copyrights.html
**************************************************************************************************/

/*
 * This header file was automatically @generated for the thaialphabet network from a template.
 * Please do not edit; instead, edit the template and regenerate.
 */

#ifndef __CNN_H__
#define __CNN_H__

#include <stdint.h>
typedef int32_t q31_t;
typedef int16_t q15_t;

/* Return codes */
#define CNN_FAIL 0
#define CNN_OK 1

/*
  SUMMARY OF OPS
  Hardware: 200,252,896 ops (199,329,408 macc; 923,488 comp; 0 add; 0 mul; 0 bitwise)
    Layer 0: 4,644,864 ops (4,478,976 macc; 165,888 comp; 0 add; 0 mul; 0 bitwise)
    Layer 1: 47,941,632 ops (47,775,744 macc; 165,888 comp; 0 add; 0 mul; 0 bitwise)
    Layer 2: 24,136,704 ops (23,887,872 macc; 248,832 comp; 0 add; 0 mul; 0 bitwise)
    Layer 3: 47,858,688 ops (47,775,744 macc; 82,944 comp; 0 add; 0 mul; 0 bitwise)
    Layer 4: 10,838,656 ops (10,653,696 macc; 184,960 comp; 0 add; 0 mul; 0 bitwise)
    Layer 5: 10,672,192 ops (10,653,696 macc; 18,496 comp; 0 add; 0 mul; 0 bitwise)
    Layer 6: 21,344,384 ops (21,307,392 macc; 36,992 comp; 0 add; 0 mul; 0 bitwise)
    Layer 7 (backbone_conv8): 10,662,944 ops (10,653,696 macc; 9,248 comp; 0 add; 0 mul; 0 bitwise)
    Layer 8 (backbone_conv9): 600,064 ops (589,824 macc; 10,240 comp; 0 add; 0 mul; 0 bitwise)
    Layer 9: 1,331,712 ops (1,331,712 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 10: 294,912 ops (294,912 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 11: 16,313,472 ops (16,313,472 macc; 0 comp; 0 add; 0 mul; 0 bitwise)
    Layer 12: 3,612,672 ops (3,612,672 macc; 0 comp; 0 add; 0 mul; 0 bitwise)

  RESOURCE USAGE
  Weight memory: 381,024 bytes out of 2,396,160 bytes total (15.9%)
  Bias memory:   936 bytes out of 8,192 bytes total (11.4%)
*/

/* Number of outputs for this network */
#define CNN_NUM_OUTPUTS 12544

/* Use this timer to time the inference */
#define CNN_INFERENCE_TIMER MXC_TMR0

/* Port pin actions used to signal that processing is active */

#define CNN_START LED_On(1)
#define CNN_COMPLETE LED_Off(1)
#define SYS_START LED_On(0)
#define SYS_COMPLETE LED_Off(0)

/* Run software SoftMax on unloaded data */
void softmax_q17p14_q15(const q31_t * vec_in, const uint16_t dim_vec, q15_t * p_out);
/* Shift the input, then calculate SoftMax */
void softmax_shift_q17p14_q15(q31_t * vec_in, const uint16_t dim_vec, uint8_t in_shift, q15_t * p_out);

/* Stopwatch - holds the runtime when accelerator finishes */
extern volatile uint32_t cnn_time;

/* Custom memcopy routines used for weights and data */
void memcpy32(uint32_t *dst, const uint32_t *src, int n);
void memcpy32_const(uint32_t *dst, int n);

/* Enable clocks and power to accelerator, enable interrupt */
int cnn_enable(uint32_t clock_source, uint32_t clock_divider);

/* Disable clocks and power to accelerator */
int cnn_disable(void);

/* Perform minimum accelerator initialization so it can be configured */
int cnn_init(void);

/* Configure accelerator for the given network */
int cnn_configure(void);

/* Load accelerator weights */
int cnn_load_weights(void);

/* Verify accelerator weights (debug only) */
int cnn_verify_weights(void);

/* Load accelerator bias values (if needed) */
int cnn_load_bias(void);

/* Start accelerator processing */
int cnn_start(void);

/* Force stop accelerator */
int cnn_stop(void);

/* Continue accelerator after stop */
int cnn_continue(void);

/* Unload results from accelerator */
int cnn_unload(uint32_t *out_buf);

/* Turn on the boost circuit */
int cnn_boost_enable(mxc_gpio_regs_t *port, uint32_t pin);

/* Turn off the boost circuit */
int cnn_boost_disable(mxc_gpio_regs_t *port, uint32_t pin);

#endif // __CNN_H__
