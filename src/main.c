/*
 * Remove any built-in C libraries to truncate output
 * Compile with:
 *      gcc -save-temps -CC -S src/main.c
 * Use main.i in CPUlator, re-add any #includes of built-in libraries in CPUlator
 */

#include "lib/hardware_constants.h"
#include "lib/device_structs.h"

// main functions
static void SetupBoard (void);

// timer utility functions
int SecondsToTicks (unsigned int seconds);
void SetTimer (unsigned int ticks);

// graphics utility functions
void Swap (int *a, int *b);
void PlotPixel (int x, int y, short int line_colour);
void ClearScreen (void);
void WaitForVSync (void);

int main (void) {
    SetupBoard();

    while (1) {
        // polling functions
    }
}

// Initialises, pauses, and resets embedded devices.
static void SetupBoard (void) {
    dTimer->CTRL = 0xA; // stop timers
    dTimer2->CTRL = 0xA;
    ClearScreen();
}

/*
 * Timer utilities
 */
int SecondsToTicks (unsigned int const seconds) {
   return (int) (seconds * TIMER_MAX);
}

void SetTimer (unsigned int const ticks) {
    dTimer->CTRL = 0xA; // stop, cont bits
    dTimer->COUNTER_START_LOW = ticks & 0xFFFF;
    dTimer->COUNTER_START_HIGH = (ticks >> 16) & 0xFFFF;
    dTimer->CTRL = 0x6; // start, cont bits
}

/*
 * Video utilities
 */
void Swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void PlotPixel (int x, int y, short int line_colour) {
    volatile short int *one_pixel_address;
    one_pixel_address = (short int*) (dPixelBuffer->BUFFER + (y << 10) + (x << 1));
    *one_pixel_address = line_colour;
}

void ClearScreen (void) {
    for (int y = 0; y < Y_MAX; y++)
        for (int x = 0; x < X_MAX; x++)
            PlotPixel(x, y, 0xFFFF);
}

void WaitForVSync (void) {
    unsigned int status;
    dPixelBuffer->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = dPixelBuffer->STATUS; // read the status register
    while (status & 0x1) // polling loop waiting for S bit to go to 0
        status = dPixelBuffer->STATUS;
    // exits when refresh done
}
