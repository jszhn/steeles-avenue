#include "ps2.h"

PS2_t *const dPS2 = (PS2_t*) PS2_BASE;

void PS2PollforChar (char cmp) {
    uint_8 exit = 0;
    char input;
    while (exit == 0) {
        if (PS2NotEmpty()) { // continuously polls PS/2 for enter key
            input = PS2Read();
            exit = input == cmp; // if enter key
        }
    }
    (void) PS2Read(); // to also clear break code
}

char PS2Read (void) {
    // POLL THIS FUNCTION CONTINUOUSLY
    if ((dPS2->RVALID) == 0)
        return NOCHAR_PS2;

    uint_8 first_b, second_b, third_b; // read bytes
    uint_8 fourth_b, fifth_b; // extra bytes for special characters
    char ret_char;

    first_b = dPS2->DATA; second_b = dPS2->DATA;
    if (first_b == SPEC_PS2) { // checks for arrow keys
        return PS2ReadSpecialCharacter (&second_b, &third_b);
    } else {
        if (first_b == BREAK_PS2) {
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