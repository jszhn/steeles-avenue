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
#include "lib/car_moving.h"

/*
 * Function definitions
 */
static void GameLoop (void);
static void SetupGame (void);

// Initialises, pauses, and resets embedded devices.
static void SetupBoard (void);

// Static screen displays.
static void StartScreen (void);
//static void PlayerCountScreen (void);
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
    uint_8 game_over = 0;
    SetupGame();   

    int x_position = X_MAX / 2, y_position = Y_MAX;
    int x_delta = 0, y_delta = 0;
    uint_8 players;
    while (game_over == 0) { // loop while game over is false
        // all of these updates the position of the player
        GetUserControl(&x_delta, &y_delta);
        if (x_delta != 0 || y_delta != 0) {
            // bounds control for sprite
            if (x_position + x_delta >= X_MAX) x_position = 0;
            else if (x_position + x_delta < 0) x_position = X_MAX - 1;
            if (y_position + y_delta >= Y_MAX) y_position = 0;
            else if (y_position + y_delta < 0) y_position = Y_MAX - 1;

            x_position += x_delta;
            y_position += y_delta;
            PlotSpriteAtColRow(x_position, y_position);
            WriteHexDisplaySingle(5, x_position);
            WriteHexDisplaySingle(0, y_position);
        }
        // reset variables to prepare for next loop
        WaitForVSync();
        x_delta = 0; y_delta = 0;
    }
}

static void SetupGame (void) {
    PlotSpriteAtColRow(7, 7);
}

static void SetupBoard (void) {
    ClearHex();
    ClearScreen();
    PS2ClearFIFO();
}

static void StartScreen (void) {
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
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
#include "lib/car_moving.c"

#endif