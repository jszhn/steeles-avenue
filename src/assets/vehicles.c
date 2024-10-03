#ifndef VEHICLES_C
#define VEHICLES_C

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

unsigned short lanes[] = {
        bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww,
        ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww,
        ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb,
};

unsigned short car[] = {
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, ly, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, rr, rr, db, db, db, db, db, db,
        rr, rr, bb, rr, rr, rr, bb, bb, bb, bb, bb, bb,
        bb, yy, ly, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, rr, rr, db, db, db, db, db, db, db,
        db, rr, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb,
        bb, yy, yy, yy, ly, yy, yy, bb, bb, bb, bb, bb, bb, bb, db, db, db, db, db, rr, db, db, db, db, db, db, db, db,
        db, db, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb,
        bb, ly, ly, ly, yy, ly, ly, yy, bb, bb, rr, rr, rr, rr, db, db, db, db, rr, rr, db, db, db, db, db, db, db, db,
        db, db, rr, rr, rr, rr, bb, bb, bb, bb, bb, bb,
        bb, ly, ly, ly, ly, yy, yy, ly, yy, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, rr, rr, rr, rr, rr, bb, gg, gg, gg, bb, bb,
        bb, yy, yy, yy, yy, ly, ly, yy, yy, yy, rr, rr, yy, rr, rr, rr, rr, rr, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, bb, bb, rr, rr, rr, gg, gg, gg, gg, gg, bb,
        bb, yy, yy, ly, ly, ly, ly, yy, yy, rr, rr, rr, rr, rr, rr, rr, rr, bb, gg, lg, bb, rr, rr, rr, rr, rr, rr, rr,
        bb, gg, lg, bb, rr, rr, gg, gg, gg, gg, gg, bb,
        bb, ly, ly, ly, yy, yy, yy, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, bb, lg, gg, bb, rr, rr, rr, rr, rr, rr, rr,
        bb, lg, gg, bb, rr, gg, gg, gg, gg, gg, gg, bb,
        bb, yy, yy, yy, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, bb, bb,
};

unsigned short go[] = {
        bb, bb, bb, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg,
        lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg,
        bb, bb, bb, bb,
        bb, bb, lg, lg, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        lg, bb, bb, bb,
        bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, lg, bb, bb,
        bb, bb, bb, bb, ww, ww, ww, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg,
        lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg,
        lg, lg, bb, bb,
        bb, bb, bb, bb, bb, lg, lg, lg, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm,
        lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm,
        lm, lm, bb, bb,
        bb, bb, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm,
        lm, lm, bb, bb,
        bb, bb, or, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm,
        lm, lm, bb, bb,
        bb, bb, lg, dg, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lm,
        lm, lm, bb, bb,
        bb, bb, gg, lg, dg, lg, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, lm, lm, lm, lm, lm, lm, lm, lm,
        lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm, lm,
        lm, lm, bb, bb,
        bb, bb, bb, gg, lg, or, ww, ww, ww, ww, ww, dg, ww, dg, ww, ww, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, bb, ww, ww, bb, bb, ww, ww, ww,
        dg, dg, bb, bb,
        bb, bb, bb, bb, gg, lg, ww, ww, ww, dg, dg, dg, dg, dg, dg, bb, gg, lg, bb, dg, dg, dg, dg, dg, dg, dg, dg, dg,
        dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, bb, gg, lg, bb, bb, gg, lg, bb, dg, dg,
        dg, dg, bb, bb,
        bb, bb, bb, bb, bb, gg, ww, dg, dg, dg, dg, dg, dg, dg, dg, bb, lg, gg, bb, dg, dg, dg, dg, dg, dg, dg, dg, dg,
        dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, dg, bb, lg, gg, bb, bb, lg, gg, bb, dg, dg,
        dg, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb,
};

unsigned short ttc[] = {
        bb, bb, bb, bb, bb, bb, bb, bb, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb,
        bb, bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, bb, bb, bb,
        bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, ww, ww, or,
        bb, ww, bb, bb,
        bb, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, or, bb,
        bb, ww, bb, bb,
        bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb,
        bb, ww, bb, bb,
        bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb,
        bb, ww, bb, bb,
        bb, bb, ww, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, bb,
        ww, rr, bb, bb,
        bb, bb, ww, gg, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, ww, bb, ww,
        rr, bb, bb, bb,
        bb, bb, ww, gg, gg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, rr, gg, gg, gg, rr, gg, gg, gg, rr, rr, gg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, ww, ww, rr,
        bb, bb, bb, bb,
        bb, bb, ww, gg, gg, gg, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, rr, rr, gg, rr, rr, rr, gg, rr, rr, gg, rr, rr, rr, rr, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb,
        bb, bb, bb, bb,
        bb, bb, ww, ww, ww, bb, gg, lg, bb, bb, gg, lg, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, gg, ww, ww, ww, gg, ww, ww, ww, gg, gg, ww, bb, gg, lg, bb, ww, ww, ww, ww, ww, ww, ww, bb, bb, bb,
        bb, bb, bb, bb,
        bb, bb, bb, ww, ww, bb, lg, gg, bb, bb, lg, gg, bb, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww,
        ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, ww, bb, lg, gg, bb, ww, ww, ww, ww, ww, ww, bb, bb, bb, bb,
        bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb,
};

unsigned short zum[] = {
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb,
        bb, bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg, lg,
        gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, bb,
        bb, bb, bb, bb,
        bb, bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg, gg,
        lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        bb, bb, bb, bb,
        bb, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg, lg,
        gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, bb, bb, bb,
        bb, bb, rr, bb, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, gg,
        lg, gg, lg, gg, lg, gg, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr, rr,
        rr, rr, bb, bb,
        bb, bb, rr, bb, bb, rr, rr, rr, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg,
        gg, lg, gg, lg, gg, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, dd, dd, dd, lg, rr, rr, rr, lg,
        lg, lg, bb, bb,
        bb, bb, rr, bb, bb, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, bb, rr, bb, dd, bb, dd, bb,
        gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, lg, bb, bb,
        bb, bb, rr, ww, bb, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        lg, lg, bb, bb,
        bb, bb, rr, rr, rr, bb, rr, bb, bb, bb, bb, bb, bb, bb, bb, bb, rr, rr, rr, bb, rr, bb, rr, bb, rr, bb, rr, bb,
        gg, lg, gg, lg, gg, lg, gg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, lg,
        lg, lg, bb, bb,
        bb, bb, bb, rr, rr, ww, rr, lg, lg, lg, lg, bb, bb, lg, lg, lg, lg, lg, rr, lg, rr, lg, rr, lg, rr, rr, rr, lg,
        gg, lg, bb, bb, gg, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, bb, lg, lg, lg, gg,
        gg, gg, bb, bb,
        bb, bb, bb, bb, rr, rr, rr, lg, lg, lg, bb, gg, lg, bb, lg, lg, lg, rr, lg, lg, rr, lg, rr, lg, rr, lg, rr, lg,
        gg, bb, gg, lg, bb, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, gg, lg, bb, lg, lg, lg,
        lg, lg, bb, bb,
        bb, bb, bb, bb, bb, rr, rr, lg, lg, lg, bb, lg, gg, bb, lg, lg, rr, rr, rr, lg, rr, rr, lg, lg, rr, lg, rr, lg,
        gg, bb, lg, gg, bb, lg, gg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, lg, bb, lg, gg, bb, lg, lg, gg,
        gg, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb,
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
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, db, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, db, db, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, db, db, lb, bb,
        bb, bb, bb, bb, bb, bb, gg, gg, gg, bb, gg, gg, bb, bb, bb, bb, bb, bb, gg, gg, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, db, db, lb, lb, bb,
        bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, bb, bb, bb, bb, gg, gg, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, db, db, lb, lb, db, bb,
        bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, lg, bb, bb, bb, lg, gg, bb, bb, lg, lg, bb, bb, bb,
        bb, bb, bb, bb, bb, db, db, lb, db, db, db, bb,
        bb, bb, bb, bb, bb, bb, gg, gg, gg, gg, lg, bb, lg, bb, lg, bb, lg, bb, lg, bb, lg, gg, lg, bb, bb, bb, gg, gg,
        gg, gg, bb, bb, db, lb, lb, db, lb, lb, lb, bb,
        bb, bb, lg, lg, lg, bb, gg, gg, gg, gg, gg, lg, gg, gg, gg, lg, gg, gg, lg, lg, lg, gg, lg, gg, gg, gg, gg, gg,
        gg, gg, gg, db, lb, db, db, lb, lb, lb, lb, bb,
        bb, lg, lg, lg, lg, lg, gg, gg, gg, bb, bb, gg, gg, gg, gg, gg, gg, gg, gg, gg, bb, bb, gg, gg, gg, gg, gg, lb,
        gg, gg, lb, db, db, lb, lb, db, db, db, db, bb,
        bb, lg, lg, lg, lg, lg, gg, gg, bb, gg, lg, bb, gg, gg, gg, gg, gg, gg, gg, bb, gg, lg, bb, gg, gg, gg, gg, gg,
        gg, gg, gg, db, db, lb, lb, lb, lb, db, db, bb,
        bb, lg, lg, lg, lg, lg, lg, gg, bb, lg, gg, bb, gg, gg, gg, gg, gg, gg, gg, bb, lg, gg, bb, gg, gg, gg, gg, gg,
        gg, gg, bb, bb, bb, db, db, db, lb, lb, lb, bb,
        bb, bb, lg, lg, lg, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb, bb,
        bb, bb, bb, bb, bb, bb, bb, bb, db, db, db, bb,
};

#endif