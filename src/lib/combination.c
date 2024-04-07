/// TIMER DELAY

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Colour definitions
 */
// grey 0x52AA
// black 0x0000
// red 0xF000
// yellow 0xFEA0
// light yellow 0xFF53
// light blue 0xCF5F
// darker blue 0x9E1B
// green 0x1E86
// light green 0x76E5
// orange 0xFD00
// light grey 0xAD55

#define gg 0x52AA // grey
#define lg 0xAD55 // light grey
#define bb 0x0000 // black
#define BLACK 0x0000
#define rr 0xF000 // red
#define yy 0xFEA0 // yellow
#define ly 0xFF53 // light yellow
#define lb 0xCF5F // light blue
#define db 0x9E1B // dark blue
#define dg 0x1E86 // dark green
#define lm 0x76E5 // light green
#define or 0xFD00 // orange
#define ww 0xFFFF // white
#define dd 0x089E // zum blue
#define pi 0xFE1B // pink

/*
 * Hardware constant definitions
 */
#define X_MAX 320
#define Y_MAX 240
#define TIMER_MAX 100000000
#define TIMERSEC 100000000

#define ONES 0b11111111111111111111111111111111

// game specific numbers
#define COL_MAX 16
#define COL_WIDTH 20

#define ROW_MAX 16
#define ROW_HEIGHT 15

/*
 * PS2 constant definitions
 */
#define NOCHAR_PS2 0x20 // used for invalid PS2 input or non-mapped characters
#define BREAK_PS2 0xF0
#define ESC_PS2 0x76
#define ENTER_PS2 0x5A
#define W_PS2 0x1D
#define A_PS2 0x1C
#define S_PS2 0x1B
#define D_PS2 0x23
#define I_PS2 0x43
#define J_PS2 0x3B
#define K_PS2 0x42
#define L_PS2 0x4B

/*
 * Nios II DE1-Soc address map
 */
#define BOARD				"DE1-SoC"

/* Memory */
#define DDR_BASE			0x40000000
#define DDR_END				0x7FFFFFFF
#define A9_ONCHIP_BASE			0xFFFF0000
#define A9_ONCHIP_END			0xFFFFFFFF
#define SDRAM_BASE			0x00000000
#define SDRAM_END			0x03FFFFFF
#define FPGA_PIXEL_BUF_BASE		0x08000000
#define FPGA_PIXEL_BUF_END		0x0803FFFF
#define FPGA_CHAR_BASE			0x09000000
#define FPGA_CHAR_END			0x09001FFF

/* Cyclone V FPGA devices */
#define LED_BASE			0xFF200000
#define LEDR_BASE			0xFF200000
#define HEX3_HEX0_BASE			0xFF200020
#define HEX5_HEX4_BASE			0xFF200030
#define SW_BASE				0xFF200040
#define KEY_BASE			0xFF200050
#define JP1_BASE			0xFF200060
#define JP2_BASE			0xFF200070
#define PS2_BASE			0xFF200100
#define PS2_DUAL_BASE			0xFF200108
#define JTAG_UART_BASE			0xFF201000
#define IrDA_BASE			0xFF201020
#define TIMER_BASE			0xFF202000
#define TIMER_2_BASE			0xFF202020
#define AV_CONFIG_BASE			0xFF203000
#define RGB_RESAMPLER_BASE    		0xFF203010
#define PIXEL_BUF_CTRL_BASE		0xFF203020
#define CHAR_BUF_CTRL_BASE		0xFF203030
#define AUDIO_BASE			0xFF203040
#define VIDEO_IN_BASE			0xFF203060
#define EDGE_DETECT_CTRL_BASE		0xFF203070
#define ADC_BASE			0xFF204000

/* Cyclone V HPS devices */
#define HPS_GPIO1_BASE			0xFF709000
#define I2C0_BASE			0xFFC04000
#define I2C1_BASE			0xFFC05000
#define I2C2_BASE			0xFFC06000
#define I2C3_BASE			0xFFC07000
#define HPS_TIMER0_BASE			0xFFC08000
#define HPS_TIMER1_BASE			0xFFC09000
#define HPS_TIMER2_BASE			0xFFD00000
#define HPS_TIMER3_BASE			0xFFD01000
#define FPGA_BRIDGE			0xFFD0501C

/*
 * Typedefs
 */
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

/*
 * Device structs
 */
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

struct timer_t {
       volatile unsigned int status;
       volatile unsigned int control;
       volatile unsigned int periodlo;
       volatile unsigned int periodhi;
       volatile unsigned int snaplo;
       volatile unsigned int snaphi;
};

struct fb_t {
    unsigned short volatile  pixels[256][512];
};

struct fb_t *const fbp = ((struct fb_t *) 0x8000000);

struct Obstacle {
	int car_type;
	int xleft;
	int xright;
	int yup;
	int ydown;
};

struct timer_t * const timer = (struct timer_t *) 0xFF202000;

/*
 * Image arrays
 */
unsigned short lanes[] = {
bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb,
};

unsigned short car[] = {
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, 
bb, ly, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, rr, rr, db, db, db, db, db, db, rr, rr, bb, rr, rr, rr, bb, bb, bb, bb, bb, bb, 
bb, yy, ly, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, rr, rr, db, db, db, db, db, db, db, db, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb, 
bb, yy, yy, yy, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, db, rr, db, db, db, db, db, db, db, db, db, db, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb, 
bb, ly, ly, ly, yy, ly, ly, yy, bb, bb, rr, rr, rr, rr, db, db, db, db, rr, rr, db, db, db, db, db, db, db, db, db, db, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb, 
bb, ly, ly, ly, ly, yy, yy, ly, yy, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, gg, gg, gg, bb, bb,
bb, yy, yy, yy, yy, ly, ly, yy, yy, yy, rr, rr, yy, rr, rr, rr, rr, rr, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, rr, rr, rr, gg, gg, gg, gg, gg, bb,
bb, yy, yy, ly, ly, ly, ly, yy, yy, rr, rr, rr, rr, rr, rr, rr, rr, bb, gg, lg, bb, rr, rr, rr, rr, rr, rr, rr, bb, gg, lg, bb, rr, rr, gg, gg, gg, gg, gg, bb,
bb, ly, ly, ly, yy, yy, yy, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, bb, lg, gg, bb, rr, rr, rr, rr, rr, rr, rr, bb, lg, gg, bb, rr, gg, gg, gg, gg, gg, gg, bb,
bb, yy, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, bb, bb,
};

unsigned short go[] = {
bb, bb, bb, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, bb, bb, bb,
bb, bb, lg, lg, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, lg, bb, bb, bb,
bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, lg, bb, bb,
bb, bb, bb, bb, ww, ww, ww, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, bb,
bb, bb, bb, bb, bb, lg, lg, lg, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, bb, bb,
bb, bb, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm, lm, lm, bb, bb,
bb, bb, or, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm, lm, lm, bb, bb,
bb, bb, lg, dg, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm, lm, lm, bb, bb,
bb, bb, gg, lg, dg, lg, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, bb, bb,
bb, bb, bb, gg, lg, or, ww, ww, ww, ww, ww, dg, ww, dg, ww, ww, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, bb, ww, ww, bb, bb, ww, ww, ww, dg, dg, bb, bb,
bb, bb, bb, bb, gg, lg, ww, ww, ww, dg, dg, dg, dg, dg, dg, bb, gg, lg, bb, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, bb, gg, lg, bb, bb, gg, lg, bb, dg, dg, dg, dg, bb, bb,
bb, bb, bb, bb, bb, gg, ww, dg, dg, dg, dg, dg, dg, dg, dg, bb, lg, gg, bb, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, bb, lg, gg, bb, bb, lg, gg, bb, dg, dg, dg, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, 
};  

unsigned short ttc[] = {
bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, bb, bb,
bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, ww, ww, or, bb, ww, bb, bb,
bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, or, bb, bb, ww, bb, bb,
bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb, bb, ww, bb, bb,
bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb, bb, ww, bb, bb,
bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb, ww, rr, bb, bb,
bb, bb, ww, gg, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, ww, rr, bb, bb, bb,
bb, bb, ww, gg, gg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, gg, gg, rr, gg, gg, gg, rr, rr, gg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, ww, ww, rr, bb, bb, bb, bb,
bb, bb, ww, gg, gg, gg, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, rr, rr, rr, gg, rr, rr, gg, rr, rr, rr, rr, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb,
bb, bb, ww, ww, ww, bb, gg, lg, bb, bb, gg, lg, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, gg, ww, ww, ww, gg, ww, ww, ww, gg, gg, ww, bb, gg, lg, bb, ww, ww, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, ww, ww, bb, lg, gg, bb, bb, lg, gg, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, lg, gg, bb, ww, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, 
};

unsigned short zum[] = {
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, 
bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb,
bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb, bb,
bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb, bb,
bb, bb, rr, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb, bb,
bb, bb, rr, bb, bb, rr, rr, rr, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, gg, lg, gg, lg, gg, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, dd, dd, dd, lg, rr, rr, rr, lg, lg, lg, bb, bb,
bb, bb, rr, bb, bb, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, bb, rr, bb, dd, bb, dd, bb, gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lg, bb, bb,
bb, bb, rr, ww, bb, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lg, lg, bb, bb,
bb, bb, rr, rr, rr, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, bb, rr, bb, rr, bb, rr, bb, rr, bb, gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lg, lg, lg, bb, bb,
bb, bb, bb, rr, rr, ww, rr, lg, lg, lg, lg, bb, bb, lg, lg, lg, lg, lg, rr, lg, rr, lg, rr, lg, rr, rr, rr, lg, gg, lg, bb, bb, gg, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, bb, lg, lg, lg, gg, gg, gg, bb, bb,
bb, bb, bb, bb, rr, rr, rr, lg, lg, lg, bb, gg, lg, bb, lg, lg, lg, rr, lg, lg, rr, lg, rr, lg, rr, lg, rr, lg, gg, bb, gg, lg, bb, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, gg, lg, bb, lg, lg, lg, lg, lg, bb, bb,
bb, bb, bb, bb, bb, rr, rr, lg, lg, lg, bb, lg, gg, bb, lg, lg, rr, rr, rr, lg, rr, rr, lg, lg, rr, lg, rr, lg, gg, bb, lg, gg, bb, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, lg, gg, bb, lg, lg, gg, gg, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
};

unsigned short raccoon[] = {
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lg, bb, bb, bb, bb,
bb, bb, bb, bb, pi, bb, bb, bb, lg, bb, lg, bb, bb, bb, bb, pi, bb, bb, bb, bb,
bb, bb, bb, bb, pi, lg, gg, gg, gg, gg, gg, gg, gg, gg, lg, pi, bb, bb, bb, bb,
bb, bb, bb, bb, lg, gg, ww, bb, gg, gg, gg, gg, ww, bb, gg, lg, bb, bb, bb, bb,
bb, bb, bb, bb, bb, gg, bb, bb, gg, gg, gg, gg, bb, bb, gg, bb, bb, bb, bb, bb,
bb, bb, bb, bb, gg, gg, gg, lg, lg, lg, lg, lg, lg, gg, gg, gg, bb, bb, bb, bb,
bb, bb, bb, bb, bb, lg, lg, lg, bb, bb, bb, bb, lg, lg, lg, bb, bb, bb, bb, bb,
bb, bb, bb, bb, lg, lg, lg, lg, lg, bb, bb, lg, lg, lg, lg, lg, bb, bb, bb, bb,
bb, bb, lg, lg, lg, lg, lg, gg, gg, gg, gg, gg, gg, lg, lg, lg, lg, lg, bb, bb,
bb, bb, bb, bb, bb, lg, lg, bb, bb, bb, bb, bb, bb, lg, lg, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, lg, lg, bb, bb, bb, bb, bb, bb, lg, lg, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
};

unsigned short black_box[] = {
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
};

unsigned short uber[] = {
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, bb,
bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, lb, bb,
bb, bb, bb, bb, bb, bb, gg, gg, gg, bb, gg, gg, bb, bb, bb, bb, bb, bb, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, lb, lb, bb,
bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, bb, bb, bb, bb, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, lb, lb, db, bb,
bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, lg, bb, bb, bb, lg, gg, bb, bb, lg, lg, bb, bb, bb, bb, bb, bb, bb, bb, db, db, lb, db, db, db, bb,
bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, bb, lg, bb, lg, bb, lg, gg, lg, bb, bb, bb, gg, gg, gg, gg, bb, bb, db, lb, lb, db, lb, lb, lb, bb,
bb, bb, lg, lg, lg, bb, gg, gg, gg, gg, gg, lg, gg, gg, gg, lg, gg, gg, lg, lg, lg, gg, lg, gg, gg, gg, gg, gg, gg, gg, gg, db, lb, db, db, lb, lb, lb, lb, bb,
bb, lg, lg, lg, lg, lg, gg, gg, gg, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, gg, gg, gg, gg, gg, lb, gg, gg, lb, db, db, lb, lb, db, db, db, db, bb,
bb, lg, lg, lg, lg, lg, gg, gg, bb, gg, lg, bb, gg, gg, gg, gg, gg, gg, gg, bb, gg, lg, bb, gg, gg, gg, gg, gg, gg, gg, gg, db, db, lb, lb, lb, lb, db, db, bb,
bb, lg, lg, lg, lg, lg, lg, gg, bb, lg, gg, bb, gg, gg, gg, gg, gg, gg, gg, bb, lg, gg, bb, gg, gg, gg, gg, gg, gg, gg, bb, bb, bb, db, db, db, lb, lb, lb, bb,
bb, bb, lg, lg, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, bb,
};

int xn = 320;
int xl = 0;
int yn = 240;
struct Obstacle cars[15];

void GetUserControl (int* x_movement, int* y_movement);

// Continuously polls PS/2 for a specific comparison character.
void PS2PollforChar (char cmp);

// Returns most recently output character. Should be polled continuously.
char PS2Read (void);

// For internal use within PS2Read(). Returns a special character.
static char PS2ReadSpecialCharacter (uint_8 *second_b, uint_8 *third_b);

// Returns non-zero if PS/2 output FIFO is empty. Returns zero if it is.
uint_8 PS2Empty (void);

// Clears PS/2 output FIFO.
void PS2ClearFIFO (void);

PIXEL_t *const dPixelBuffer = (PIXEL_t*) PIXEL_BUF_CTRL_BASE;

static void GameLoop (void);
static void SetupGame (void);

// Initialises, pauses, and resets embedded devices.
static void SetupBoard (void);

// Static screen displays.
static void StartScreen (void);
//static void PlayerCountScreen (void);
static void EndScreen (void);

void WaitForVSync (void);
void GetUserControl (int* x_movement, int* y_movement);
void waitasec(int pow_fraction);
void instantiate_cars();
void sprite_draw(struct fb_t *const fbp, unsigned short sprite[], int x, int y, int size);
void sprite_scroll(struct fb_t *const fbp;);
void solid_color(struct fb_t *const fbp, unsigned short color);
void PlotSpriteAtColRow (const uint_8 row, const uint_8 col);

/*

                        PS2 STUFF


*/

PS2_t *const dPS2 = (PS2_t*) PS2_BASE;

void GetUserControl (int* x_movement, int* y_movement) {
//    while (PS2Empty() == 0) {
        char in = PS2Read();
        switch (in) {
            case 'W':
                *y_movement = -1;
                break;
            case 'A':
                *x_movement = -1;
                break;
            case 'S':
                *y_movement = 1;
                break;
            case 'D':
                *x_movement = 1;
                break;
            default:
                *x_movement = *x_movement;
                *y_movement = *y_movement;
        }
//    }
}

void PS2PollforChar (char cmp) {
    uint_8 exit = 0;
    char input;
    while (exit == 0) { // continuously polls PS/2 for enter key
        if (PS2Empty() == 0) { // if FIFO not empty
            input = PS2Read();
            exit = (input == cmp); // if enter key
        }
    }
    (void) PS2Read(); // to also clear break code
}

char PS2Read (void) {
    // POLL THIS FUNCTION CONTINUOUSLY
    if (PS2Empty())
        return NOCHAR_PS2;

    uint_8 first_b, second_b, third_b; // read bytes
    first_b = dPS2->DATA; second_b = dPS2->DATA; third_b = dPS2->DATA;

    if (first_b == BREAK_PS2) {
        return NOCHAR_PS2;
    }
    switch (first_b) {
        case (W_PS2):
            return 'W';
        case (A_PS2):
            return 'A';
        case (S_PS2):
            return 'S';
        case (D_PS2):
            return 'D';
        case (I_PS2):
            return 'I';
        case (J_PS2):
            return 'J';
        case (K_PS2):
            return 'K';
        case (L_PS2):
            return 'L';
        case (ESC_PS2):
            return '~';
        case (ENTER_PS2):
            return '\n';
        default:
            return NOCHAR_PS2;
    }

}

uint_8 PS2Empty (void) { // true if empty, false if there's elements
    return (dPS2->RVALID & 0b10000000) == 0;
}

void PS2ClearFIFO (void) {
    uint_8 input_byte;
    while (PS2Empty())
        input_byte = dPS2->DATA; // flushes queue
}

/*

                        END OF PS2 STUFF


*/

void waitasec(int pow_fraction) {
	   unsigned int t = TIMERSEC >> pow_fraction;
       timer->control = 0x8; // stop the timer
       timer->status = 0; // reset TO
       timer->periodlo = (t & 0x0000FFFF);
       timer->periodhi = (t & 0xFFFF0000) >> 16;
       timer->control = 0x4;
       while ((timer->status & 0x1) == 0);
          timer->status = 0; // reset TO
}

void instantiate_cars(){
		for (int i = 0; i < 16; i++){
			cars[i].car_type = rand() % 5;
			cars[i].yup = i*15 + 15;
			cars[i].ydown = i*15 + 30;
			cars[i].xleft = rand() % 320;
			if(cars[i].car_type == 0 || cars[i].car_type == 2 || cars[i].car_type == 3){
				cars[i].xright = cars[i].xright + 60;
			}
			if(cars[i].car_type == 1 || cars[i].car_type == 4){
				cars[i].xright = cars[i].xright + 40;
			}
		}
}

void sprite_draw(struct fb_t *const fbp, unsigned short sprite[], int x, int y, int size) {
 int sxi, syi;
 int xi, yi;
	if(size == 4){
		for (sxi = 0; sxi < 320; sxi++)
			for (syi = 0; syi < 1; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*320+sxi];
		}
	}
	if(size == 3){
		for (sxi = 0; sxi < 60; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*60+sxi];
		}
	}
	if(size == 2){
		for (sxi = 0; sxi < 40; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*40+sxi];
		}
	}
	if(size == 1){
		for (sxi = 0; sxi < 20; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*20+sxi];
		}
	}
}
/*
void sprite_scroll(struct fb_t *const fbp;) {
	int x, y;
	for(int y = 13; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	for(int y = 14; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	// array to store location, only need x for loop, update locations, etc etc etc
	while (1){
		for (x = 0; x < 320; x += 1){
			for (int i = 0; i < 16; i += 1){
				
				if (cars[i].car_type == 0){
					sprite_draw(fbp, ttc, cars[i].xleft + x, cars[i].yup, 3);
				} else if (cars[i].car_type == 1){
					sprite_draw(fbp, uber, cars[i].xleft + x, cars[i].yup, 2);
				} else if (cars[i].car_type == 2){
					sprite_draw(fbp, go, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 3){
					sprite_draw(fbp, zum, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 4){
					sprite_draw(fbp, car, 320-(cars[i].xleft + x), cars[i].yup, 2);
				}
				// boundary checks COMMENTED OUT UNTIL IMPLEMENTED
				
				if (cars[i].car_type == 1 || cars[i].car_type == 4){
					if(car[i].yup == y_position*ROW_HEIGHT){
						if(cars[i].xleft + x < (x_position*COL_WIDTH + 20){
							x_position = 8;
							y_position = 14;
							sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
							// score = 0;
						}
					}
				}
				if (cars[i].car_type == 0 || cars[i].car_type == 2 || cars[i].car_type == 3){
					if(car[i].yup == y_position*ROW_HEIGHT){
						if(cars[i].xright + x > x_position*COL_WIDTH){
							x_position = 8;
							y_position = 14;
							sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
							// score = 0;
						}
					}
				}
				
				
			}
		}
		solid_color(fbp, 0x0000);
			int x;
			int y;
			for(int y = 13; y < 230; y+=15){
				sprite_draw(fbp, lanes, x, y, 4);
			}
			for(int y = 14; y < 230; y+=15){
				sprite_draw(fbp, lanes, x, y, 4);
			}
	}
}
*/

void solid_color(struct fb_t *const fbp, unsigned short color) {
    int x, y;
	for (x = 0; x < xn; x++)
       for (y = 0; y < yn; y++) 
          fbp->pixels[y][x] = color; // set pixel value at x,y
}

static void GameLoop (void) {
    uint_8 game_over = 0;
    //SetupGame();   
	int x, y;
		for(int y = 13; y < 230; y+=15){
			sprite_draw(fbp, lanes, x, y, 4);
		}
		for(int y = 14; y < 230; y+=15){
			sprite_draw(fbp, lanes, x, y, 4);
		}

    int x_position = 8, y_position = 14;
    int x_delta = 0, y_delta = 0;
    uint_8 players;
	
    while (game_over == 0) { // loop while game over is false
        // all of these updates the position of the player
		
		int x, y;
		for(int y = 13; y < 230; y+=15){
			sprite_draw(fbp, lanes, x, y, 4);
		}
		for(int y = 14; y < 230; y+=15){
			sprite_draw(fbp, lanes, x, y, 4);
		}
		
		for (x = 0; x < 520; x += 1){
			
			for (int i = 0; i < 16; i += 1){
				if (y_position*ROW_HEIGHT < 15){
					sprite_draw(fbp, black_box, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
				//solid_color(fbp, 0x0000);
			x_position = 8;
			y_position = 14;
			sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
		}		
				/*
				if (cars[i].car_type == 0 || cars[i].car_type == 2 || cars[i].car_type == 3){
					if(cars[i].yup == y_position*ROW_HEIGHT){
						if((cars[i].xleft + x) < (x_position*COL_WIDTH)){
							x_position = 8;
							y_position = 14;
							sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
							// score = 0;
						}
					}
				}
				if (cars[i].car_type == 1 || cars[i].car_type == 4){
					if(cars[i].yup == y_position*ROW_HEIGHT){
						if((cars[i].xleft + x) < (x_position*COL_WIDTH)){
							x_position = 8;
							y_position = 14;
							sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
							// score = 0;
						}
					}
				}
				*/
				if (x_position*COL_WIDTH == (cars[i].xleft + x) && y_position*ROW_HEIGHT == cars[i].yup) {
                x_position = 8;
                y_position = 14;
					sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
            }
				
				if (cars[i].car_type == 0){
					sprite_draw(fbp, ttc, cars[i].xleft + x, cars[i].yup, 3);
				} else if (cars[i].car_type == 1){
					sprite_draw(fbp, uber, cars[i].xleft + x, cars[i].yup, 2);
				} else if (cars[i].car_type == 2){
					sprite_draw(fbp, go, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 3){
					sprite_draw(fbp, zum, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 4){
					sprite_draw(fbp, car, 320-(cars[i].xleft + x), cars[i].yup, 2);
				}
			}
			GetUserControl(&x_delta, &y_delta);

        if (x_delta == 0 && y_delta == 0) continue;
        //iteLEDSingle(8);
		sprite_draw(fbp, black_box, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
        // bounds control for sprite
        if (x_position + x_delta >= X_MAX) x_position = 0;
        else if (x_position + x_delta < 0) x_position = X_MAX - 1;
        if (y_position + y_delta >= Y_MAX) y_position = 0;
        else if (y_position + y_delta < 0) y_position = Y_MAX - 1;

        x_position += x_delta; y_position += y_delta;
        sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
		//PlotSpriteAtColRow(x_position, y_position);

        // reset variables to prepare for next loop
        WaitForVSync();
        x_delta = 0; y_delta = 0;
		
		if (x_position*ROW_HEIGHT < 15){
			sprite_draw(fbp, black_box, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
			x_position = 15;
			sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
		} else if (x_position*ROW_HEIGHT > 215){
			sprite_draw(fbp, black_box, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
			x_position = 0;
			sprite_draw(fbp, raccoon, x_position*COL_WIDTH, y_position*ROW_HEIGHT, 1);
		}
		}
		
        
		
		// if raccoon has reached the top
		
    }
}

static void SetupGame (void) {
    PlotSpriteAtColRow(7, 7);
}

static void SetupBoard (void) {
    ClearHex();
    ClearScreen();
    PS2ClearFIFO();
}

static void StartScreen (void) {
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
}

static void EndScreen (void) {
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
}

void WaitForVSync (void) {
    unsigned int status;
    dPixelBuffer->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = dPixelBuffer->STATUS; // read the status register
    while (status & 0x1) // polling loop waiting for S bit to go to 0
        status = dPixelBuffer->STATUS;
    // exits when refresh done
}

void PlotSpriteAtColRow (const uint_8 row, const uint_8 col) {
        // currently only plots a single pixel at a time
        if (row >= ROW_MAX || col >= COL_MAX) // if invalid row/col
            return;

        uint_32 x = col * COL_WIDTH;
        uint_32 y = row * ROW_HEIGHT;
		fbp->pixels[x][y] = BLACK;
}


int main() {
    /*SetupBoard();

    while (1) { // main outer loop
        StartScreen();
        GameLoop(); // loops game
        EndScreen();
    }
    */

  solid_color(fbp, 0x0000); // make all pixels white
  instantiate_cars();
  //sprite_scroll(fbp);
  while (1){
  	GameLoop();
  }
}
