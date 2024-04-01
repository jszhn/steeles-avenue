/// TIMER DELAY

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct timer_t {
       volatile unsigned int status;
       volatile unsigned int control;
       volatile unsigned int periodlo;
       volatile unsigned int periodhi;
       volatile unsigned int snaplo;
       volatile unsigned int snaphi;
};


struct timer_t * const timer = (struct timer_t *) 0xFF202000;

#define TIMERSEC 100000000

void
waitasec(int pow_fraction) {
	   unsigned int t = TIMERSEC >> pow_fraction;
       timer->control = 0x8; // stop the timer
       timer->status = 0; // reset TO
       timer->periodlo = (t & 0x0000FFFF);
       timer->periodhi = (t & 0xFFFF0000) >> 16;
       timer->control = 0x4;
       while ((timer->status & 0x1) == 0);
          timer->status = 0; // reset TO
}


// 16x16 sprites as unidimensional arrays :(
// converted from:
// https://opengameart.org/content/chibi-monsters-set-01
// made by ansimuz.com

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
unsigned short lanes[] = {bb, bb, bb}
unsigned short car[] = {bb, yy, ly}
unsigned short go[] = {lg, ww, bb}
unsigned short ttc[] = {yy, rr, ly}
unsigned short zum[] = {bb, rr, lg}
unsigned short raccoon[] = {rr, yy, bb}
unsigned short uber[] = {ww, bb, yy}
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

struct Obstacle cars[15];

void instantiate_cars(){
		for (int i = 0; i < 16; i++){
			cars[i].car_type = rand() % 5;
			cars[i].yup = i*15 + 15;
			cars[i].xleft = rand() % 320;
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

int xn = 320;
int xl = 0;
int yn = 240;

void
sprite_scroll(struct fb_t *const fbp;) {
	int x, y;
	for(int y = 13; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	for(int y = 14; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	// array to store location, only need x for loop, update locations, etc etc etc
	while (1){
		for (x = 0; x < 500; x += 1){
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
	
			/*
	while (1){
		for (x = 0; x < 380; x+=1){
			
			sprite_draw(fbp, ttc, x, 110, 3);
			sprite_draw(fbp, uber, x, 140, 2);
			sprite_draw(fbp, raccoon, x, 155, 1);
		
			sprite_draw(fbp, go, 320-x, 80, 3);
			sprite_draw(fbp, zum, 320-x, 95, 3);
			sprite_draw(fbp, car, 320-x, 125, 2);
		}
	}
	for (x = 320; x > xl; x-=1){
		sprite_draw(fbp, go, x, 80, 3);
		sprite_draw(fbp, zum, x, 100, 3);
		sprite_draw(fbp, car, x, 140, 2);
	}
	*/
}


void
solid_color(struct fb_t *const fbp, unsigned short color) {
    int x, y;
	for (x = 0; x < xn; x++)
       for (y = 0; y < yn; y++) 
          fbp->pixels[y][x] = color; // set pixel value at x,y
}


int
main() {
	
  solid_color(fbp, 0x0000); // make all pixels white
  instantiate_cars();
  sprite_scroll(fbp);
}