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
#include "lib/other_devices.h"

// Initialises, pauses, and resets embedded devices.
static void SetupBoard (void);

// Initial screen display.
static void StartScreen (void);

// After start screen, allows user to select number of players.
static void PlayerCountScreen (void);

int main (void) {
    SetupBoard();
    StartScreen();

    while (1) {
//        if ((dPS2->RVALID & 0x8000) != 0)
//            WriteHexDisplaySingle(0, 1);
    }
}

static void SetupBoard (void) {
    dTimer->CTRL = 0xA; // stop timers
    dTimer2->CTRL = 0xA;
    *dHEX74 = 0x0;
    *dHEX30 = 0x0;
    ClearScreen();
}

static void StartScreen (void) {
    // draw art

    uint_8 exit = 0;
    while (exit == 0) {
        if ((dPS2->RVALID & 0x8000) != 0) { // continuously polls PS2 for enter key
//            ReadPS2();
            exit = 1;
        }
    }
}

static void PlayerCountScreen (void) {
    // idk how feasible this is
}

// This ensures that GCC combines all relevant code into one file.
// If a new helper .c file is created, please #include it here.
#ifdef CPULATOR

#include "lib/graphics.c"
#include "lib/other_devices.c"

#endif