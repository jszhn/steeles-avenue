#include "graphics.h"

PIXEL_t *const dPixelBuffer = (PIXEL_t*) PIXEL_BUF_CTRL_BASE;

static void Swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

uint_16 RGBtoColour (uint_8 red, uint_8 green, uint_8 blue) {
    return (blue | (green << 5) | (red << 11));
}

void PlotPixel (uint_32 x, uint_32 y, short int line_colour) {
    volatile short int *one_pixel_address;
    one_pixel_address = (short int*) (dPixelBuffer->BUFFER + (y << 10) + (x << 1));
    *one_pixel_address = line_colour;
}

void ClearScreen (void) {
    for (int y = 0; y < Y_MAX; y++) // iterate through each pixel
        for (int x = 0; x < X_MAX; x++)
            PlotPixel(x, y, WHITE);
}

void WaitForVSync (void) {
    unsigned int status;
    dPixelBuffer->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = dPixelBuffer->STATUS; // read the status register
    while (status & 0x1) // polling loop waiting for S bit to go to 0
        status = dPixelBuffer->STATUS;
    // exits when refresh done
}