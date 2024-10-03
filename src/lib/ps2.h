//
// PS2 utilities and mapping
//

#ifndef PS2_H
#define PS2_H

#include "device_structs.h"

/*
 * Preprocessor definitions
 */

#define NOCHAR_PS2 0x20 // used for invalid PS2 input or non-mapped characters
#define BREAK_PS2 0xF0
#define ESC_PS2 0x76
#define ENTER_PS2 0x5A
#define W_PS2 0x1D
#define A_PS2 0x1C
#define S_PS2 0x1B
#define D_PS2 0x23
#define I_PS2 0x43
#define J_PS2 0x3B
#define K_PS2 0x42
#define L_PS2 0x4B

/*
 * Function definitions
 */

// Gets user control from PS/2 keyboard.
void GetUserControl(int *x_movement, int *y_movement);
// Continuously polls PS/2 for a specific comparison character.
void PS2PollforChar(char cmp);
// Returns most recently output character. Should be polled continuously.
char PS2Read(void);
// For internal use within PS2Read(). Returns a special character.
static char PS2ReadSpecialCharacter(uint_8 *second_b, uint_8 *third_b);
// Returns non-zero if PS/2 output FIFO is empty. Returns zero if it is.
uint_8 PS2Empty(void);
// Clears PS/2 output FIFO.
void PS2ClearFIFO(void);

#endif
