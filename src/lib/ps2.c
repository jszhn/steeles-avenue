#include "ps2.h"

PS2_t *const dPS2 = (PS2_t*) PS2_BASE;

/*
* PS/2 functions + utilities
*/
void GetUserControl(int *x_movement, int *y_movement) {
    char in = PS2Read();
    switch (in) {
        case 'W':
            *y_movement = -1;
            break;
        case 'A':
            *x_movement = -1;
            break;
        case 'S':
            *y_movement = 1;
            break;
        case 'D':
            *x_movement = 1;
            break;
        default:
            *x_movement = *x_movement;
            *y_movement = *y_movement;
    }
}

void PS2PollforChar(char cmp) {
    uint_8 exit = 0;
    char input;
    while (exit == 0) { // continuously polls PS/2 for enter key
        if (PS2Empty() == 0) { // if FIFO not empty
            input = PS2Read();
            exit = (input == cmp); // if enter key
        }
    }
    (void) PS2Read(); // to also clear break code
}

char PS2Read(void) {
    // POLL THIS FUNCTION CONTINUOUSLY
    if (PS2Empty())
        return NOCHAR_PS2;

    uint_8 first_b, second_b, third_b; // read bytes
    first_b = dPS2->DATA;
    second_b = dPS2->DATA;
    third_b = dPS2->DATA;

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
        case (ENTER_PS2):
            return '\n';
        default:
            return NOCHAR_PS2;
    }

}

inline uint_8 PS2Empty(void) { // true if empty, false if there's elements
    return (dPS2->RVALID & 0b10000000) == 0;
}

void PS2ClearFIFO(void) {
    uint_8 input_byte;
    while (PS2Empty())
        input_byte = dPS2->DATA; // flushes queue
}