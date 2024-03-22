//
// Structs for various parallel port devices on the DE1-SoC.
//

#ifndef DEVICE_DEVICES_H
#define DEVICE_DEVICES_H

#include "address_map_nios2.h"

// 32-bit volatile unsigned integer
typedef volatile unsigned int vuint_32;
// 16-bit volatile unsigned integer
typedef volatile unsigned short int vuint_16;
// 8-bit volatile unsigned integer
typedef volatile unsigned char vuint_8;

// 32-bit unsigned integer
typedef unsigned int uint_32;
// 16-bit unsigned integer
typedef unsigned short int uint_16;
// 8-bit unsigned integer (char)
typedef unsigned char uint_8;

typedef struct AUDIO_t {
    volatile unsigned int CTRL;
    volatile unsigned char RARC;
    volatile unsigned char RALC;
    volatile unsigned char WSRC;
    volatile unsigned char WSLC;
    volatile unsigned int LDATA;
    volatile unsigned int RDATA;
} AUDIO_t;

typedef struct TIMER_t {
    volatile unsigned int STATUS;
    volatile unsigned int CTRL;
    volatile unsigned int COUNTER_START_LOW;
    volatile unsigned int COUNTER_START_HIGH;
    volatile unsigned int COUNTER_SNAP_LOW;
    volatile unsigned int COUNTER_SNAP_HIGH;
} TIMER_t;

typedef struct PIT_t {
    volatile unsigned int DR;
    volatile unsigned int DIR;
    volatile unsigned int MASK;
    volatile unsigned int EDGE;
} PIT_t;

typedef struct PIXEL_t {
    vuint_32 BUFFER;
    vuint_32 BACK_BUFFER;
    vuint_32 RES;
    vuint_32 STATUS;
} PIXEL_t;

typedef struct PS2_t {
    vuint_16 DATA; // only first 8 bits of DATA is used
    vuint_16 REG;
    vuint_32 CTRL;
} PS2_t;

AUDIO_t *const dAudio = (AUDIO_t*) AUDIO_BASE;
TIMER_t *const dTimer = (TIMER_t*) TIMER_BASE;
TIMER_t *const dTimer2 = (TIMER_t*) TIMER_2_BASE;
vuint_32 *const dLEDs = (vuint_32*) LEDR_BASE;
vuint_32 *const dHEX30 = (vuint_32*) HEX3_HEX0_BASE;
vuint_32 *const dHEX74 = (vuint_32*) HEX5_HEX4_BASE;
PIXEL_t *const dPixelBuffer = (PIXEL_t*) PIXEL_BUF_CTRL_BASE;
PS2_t *const dPS2 = (PS2_t*) PS2_BASE;

#endif