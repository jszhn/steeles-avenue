#include "ps2.h"

char PS2Read (void) {
    // POLL THIS FUNCTION CONTINUOUSLY
    uint_8 first_b, second_b; // read bytes
    uint_8 third_b; // extra bytes for special characters
    char ret_char;

    if ((dPS2->RVALID) == 0)
        return NOCHAR_PS2;

    first_b = dPS2->DATA;
    if (first_b == SPEC_PS2) { // checks for arrow keys
        return PS2ReadSpecialCharacter (&second_b, &third_b);
    } else {
        if (first_b == BREAK_PS2) {
            second_b = dPS2->DATA;
            return NOCHAR_PS2;
        }
        switch (first_b) {
            case (W_PS2):
                return 'W';
            case (A_PS2):
                return 'A';
            case (S_PS2):
                return 'S';
            case (D_PS2):
                return 'D';
            case (ESC_PS2):
                return '~';
            case (ENTER_PS2):
                return '\n';
            default:
                return NOCHAR_PS2;
        }
    }
}

static char PS2ReadSpecialCharacter (uint_8 *second_b, uint_8 *third_b) {
    *second_b = dPS2->DATA;
    if (*second_b == BREAK_PS2) { // checks for break key
        *third_b = dPS2->DATA; // clears next key in output FIFO
        return NOCHAR_PS2;
    } else {
        switch (*second_b) {
            case (LEFT_PS2):
                return 'H';
            case (DOWN_PS2):
                return 'J';
            case (UP_PS2):
                return 'K';
            case (RIGHT_PS2):
                return 'L';
            default: return NOCHAR_PS2;
        }
    }
}

uint_8 PS2NotEmpty (void) {
    return (dPS2->RVALID & 0x8000) != 0;
}

void PS2ClearFIFO (void) {
    static uint_8 ps2_byte;
    while (PS2NotEmpty())
        ps2_byte = dPS2->DATA; // flushes queue
}