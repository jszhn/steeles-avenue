//
// VGA graphics utilities for the DE1-SoC.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "device_structs.h"
#include "hardware_constants.h"

// colours
#define WHITE 0xFFFF
#define BLACK 0x0

// Swaps the values of two pointers. Used internally.
static void Swap (int *a, int *b);

// Returns a short int containing a colour value.
uint_16 RGBtoColour (uint_8 red, uint_8 green, uint_8 blue);

// Plots a pixel on the screen given x, y coordinates.
void PlotPixel (uint_32 x, uint_32 y, short int line_colour);

// Blanks the screen with white.
void ClearScreen (void);

// Waits for monitor's refresh to sync.
void WaitForVSync (void);

#endif
