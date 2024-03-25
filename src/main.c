/*
 * Remove any built-in C libraries to truncate output
 * Compile with:
 *      gcc -save-temps -CC -S src/main.c
 * Use main.i in CPUlator, re-add any #includes of built-in libraries in CPUlator
 */

// For use in #include guards at the bottom of this file. If not using CPUlator, please comment this definition out!
//#define CPULATOR

#include "lib/hardware_constants.h"
#include "lib/device_structs.h"
#include "lib/graphics.h"
#include "lib/ps2.h"
#include "lib/other_devices.h"

/*
 * Function definitions
 */
static void GameLoop (void);

// Initialises, pauses, and resets embedded devices.
static void SetupBoard (void);

// Static screen displays.
static void StartScreen (void);
static void PlayerCountScreen (void);
static void EndScreen (void);

/*
 * Main code
 */
int main (void) {
    SetupBoard();

    while (1) { // main outer loop
        StartScreen();
        GameLoop(); // loops game
        EndScreen();
    }
}

static void GameLoop (void) {

}

static void SetupBoard (void) {
    dTimer->CTRL = 0xA; // stop timers
    dTimer2->CTRL = 0xA;
    *dHEX74 = 0x0;
    *dHEX30 = 0x0;
    ClearScreen();
    PS2ClearFIFO();
}

static void StartScreen (void) {
    // draw art

    // PS/2 polling for exit condition
    uint_8 exit = 0;
    char input;
    while (exit == 0) {
        if (PS2NotEmpty()) { // continuously polls PS/2 for enter key
            input = PS2Read();
            exit = input == '\n'; // if enter key
        }
    }
}

static void PlayerCountScreen (void) {
    // idk how feasible this is
}

static void EndScreen (void) {
    // draw art

    // PS/2 polling for exit condition
    uint_8 exit = 0;
    char input;
    while (exit == 0) {
        if (PS2NotEmpty()) { // continuously polls PS/2 for enter key
            input = PS2Read();
            exit = input == '\n'; // if enter key
        }
    }
}

// This ensures that GCC combines all relevant code into one file.
// If a new helper .c file is created, please #include it here.
#ifdef CPULATOR

#include "lib/graphics.c"
#include "lib/ps2.c"
#include "lib/other_devices.c"

#endif