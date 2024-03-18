/*
 * Compile with:
 *      gcc -save-temps -CC -Wall -S src/main.c
 * Use main.i in CPUlator
 */

#include "lib/hardware_constants.h"
#include "lib/device_structs.h"

// main functions
static void SetupBoard (void);

// graphics utility functions
void PlotPixel (int x, int y, short int line_colour);
void ClearScreen (void);

int main (void) {
    SetupBoard();
    ClearScreen();
    return 0;
}

// Initialises, pauses, and resets embedded devices.
void SetupBoard (void) {
    dTimer->CTRL = 0xA; // stop timers
    dTimer2->CTRL = 0xA;
}

// Plots an individual pixel on the screen.
void PlotPixel (int x, int y, short int line_colour) {
    volatile short int *one_pixel_address;
    one_pixel_address = (int*) ((int) *dPixelBuffer + (y << 10) + (x << 1));
    *one_pixel_address = line_colour;
}

// Draws all black to screen.
void ClearScreen (void) {
    for (int y = 0; y < Y_MAX; y++)
        for (int x = 0; x < X_MAX; x++)
            PlotPixel(x, y, 0xFFFF);
}