//
// Structs for various parallel port devices on the DE1-SoC.
//

#ifndef DEVICE_STRUCTS_H
#define DEVICE_STRUCTS_H

#include "address_map_nios2.h"

// 32-bit volatile unsigned integer
typedef volatile unsigned int vuint_32;
// 16-bit volatile unsigned integer
typedef volatile unsigned short int vuint_16;
// 8-bit volatile unsigned integer (char)
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
    vuint_8 DATA;
    vuint_8 RVALID; // only MSB is used
    vuint_16 RAVAIL;
    vuint_32 CTRL;
} PS2_t;

#endif