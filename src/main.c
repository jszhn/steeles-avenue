/*
 * Remove any built-in C libraries to truncate output
 * Compile with:
 *      gcc -save-temps -CC -S src/main.c
 * Use main.i in CPUlator, re-add any #includes of built-in libraries in CPUlator
 */

// For use in #include guards. If not using CPUlator, please comment this definition out!
#define CPULATOR

#include "lib/hardware_constants.h"
#include "lib/device_structs.h"
#include "lib/graphics.h"

// main functions
static void SetupBoard (void);

// timer utility functions
int SecondsToTicks (double seconds);
void SetTimer (unsigned int ticks);

// other device utility functions
void WriteLEDSingle (uint_8 integer_write_value);
void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value);

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
int SecondsToTicks (double const seconds) {
   return (int) (seconds * TIMER_MAX);
}

void SetTimer (unsigned int const ticks) {
    dTimer->CTRL = 0xA; // stop, cont bits
    dTimer->COUNTER_START_LOW = ticks & 0xFFFF;
    dTimer->COUNTER_START_HIGH = (ticks >> 16) & 0xFFFF;
    dTimer->CTRL = 0x6; // start, cont bits
}

/*
 * Other device utilities
 */
void WriteLEDSingle (uint_8 integer_write_value) {
    if (integer_write_value > 9) integer_write_value = 9;
    *dLEDs = 0x1 << integer_write_value;
}

void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value) {
    // display num ranges from 0-7
    write_value = write_value & 0b1111111; // truncate write value to ensure no interference
    vuint_32* display_addr;

    if (display_num > 3) {
        display_addr = dHEX74;
        display_num -= 4;
    } else
        display_addr = dHEX30;

    uint_32 temp = *display_addr & (0x0 << (display_num * 8)); // clears specific display without overwriting others
    *display_addr = temp | (write_value << (display_num * 8)); // writes to HEX display
}

// This ensures that GCC combines all relevant code into one file. If a new helper .c file is created, please #include it here.
#ifdef CPULATOR

#include "lib/graphics.c"

#endif