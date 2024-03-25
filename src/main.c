/*
 * Remove any built-in C libraries to truncate output
 * Compile with:
 *      gcc -save-temps -CC -S src/main.c
 * Use main.i in CPUlator, re-add any #includes of built-in libraries in CPUlator
 */

// For use in #include guards at the bottom of this file. If not using CPUlator, please comment this definition out!
#define CPULATOR

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
    ClearHex();
    ClearScreen();
    PS2ClearFIFO();
}

static void StartScreen (void) {
    PS2PollforChar('\n'); // checks for 'enter' key
    WriteHexDisplayFull(0xF);
    PS2ClearFIFO();
}

static void PlayerCountScreen (void) {
    // idk how feasible this is
}

static void EndScreen (void) {
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
}

// This ensures that GCC combines all relevant code into one file.
// If a new helper .c file is created, please #include it here.
#ifdef CPULATOR

#include "lib/graphics.c"
#include "lib/ps2.c"
#include "lib/other_devices.c"

#endif