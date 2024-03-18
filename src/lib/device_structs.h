//
// Structs for various parallel port devices on the DE1-SoC.
//

#ifndef DEVICE_DEVICES_H
#define DEVICE_DEVICES_H

#include "address_map_nios2.h"

// 32-bit unsigned volatile integer
typedef volatile unsigned int vuint_32;

// 8-bit unsigned volatile char
typedef volatile unsigned char vuchar_8;

typedef struct AUDIO_t {
    volatile unsigned int CTRL;
    volatile unsigned char RARC;
    volatile unsigned char RALC;
    volatile unsigned char WSRC;
    volatile unsigned char WSLC;
    volatile unsigned int LDATA;
    volatile unsigned int RDATA;
} AUDIO_t;

typedef struct PIT_t {
    volatile unsigned int DR;
    volatile unsigned int DIR;
    volatile unsigned int MASK;
    volatile unsigned int EDGE;
} PIT_t;

typedef struct TIMER_t {
    volatile unsigned int STATUS;
    volatile unsigned int CTRL;
    volatile unsigned int COUNTER_START_LOW;
    volatile unsigned int COUNTER_START_HIGH;
    volatile unsigned int COUNTER_SNAP_LOW;
    volatile unsigned int COUNTER_SNAP_HIGH;
} TIMER_t;

AUDIO_t *const dAudio = (AUDIO_t*) AUDIO_BASE;
TIMER_t *const dTimer = (TIMER_t*) TIMER_BASE;
TIMER_t *const dTimer2 = (TIMER_t*) TIMER_2_BASE;
vuint_32 *const dLEDs = (vuint_32*) LEDR_BASE;
vuint_32 *const dHEX30 = (vuint_32*) HEX3_HEX0_BASE;
PIT_t *const dHEX74 = (PIT_t*) HEX5_HEX4_BASE;
volatile int *dPixelBuffer = (int*) PIXEL_BUF_CTRL_BASE;
PIT_t *const dPS2 = (PIT_t*) PS2_BASE; // only DR/DIR is used; accessing MASK/EDGE do nothing

#endif