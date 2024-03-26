#include "ps2.h"

PS2_t *const dPS2 = (PS2_t*) PS2_BASE;

void GetUserControl (uint_8* player_num, int* x_movement, int* y_movement) {
    *player_num = 0; // stores player num as binary num; bit 0: player 0, bit 1: player 1
    while (PS2Empty() == 0) {
        char in = PS2Read();
        WriteHexDisplayFull(in);
        switch (in) {
            case 'W':
                *y_movement = 1;
                *player_num |= 0x1;
                break;
            case 'A':
                *x_movement = -1;
                *player_num |= 0x1;
                break;
            case 'S':
                *y_movement = -1;
                *player_num |= 0x1;
                break;
            case 'D':
                *x_movement = 1;
                *player_num |= 0x1;
                break;
            case 'J':
                *(x_movement + 1) = -1;
                *player_num |= 0x2;
                break;
            case 'K':
                *(y_movement + 1) = -1;
                *player_num |= 0x2;
                break;
            case 'I':
                *(y_movement + 1) = 1;
                *player_num |= 0x2;
                break;
            case 'L':
                *(x_movement + 1) = 1;
                *player_num |= 0x2;
                break;
//            case '~': // pause screen
            default:
                *x_movement = 0;
                *y_movement = 0;
        }
    }
}

void PS2PollforChar (char cmp) {
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

char PS2Read (void) {
    // POLL THIS FUNCTION CONTINUOUSLY
    if ((dPS2->RVALID) == 0)
        return NOCHAR_PS2;

    uint_8 first_b, second_b, third_b; // read bytes
    first_b = dPS2->DATA; second_b = dPS2->DATA; third_b = dPS2->DATA;

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
        case (I_PS2):
            return 'I';
        case (J_PS2):
            return 'J';
        case (K_PS2):
            return 'K';
        case (L_PS2):
            return 'L';
        case (ESC_PS2):
            return '~';
        case (ENTER_PS2):
            return '\n';
        default:
            return NOCHAR_PS2;
    }

}

uint_8 PS2Empty (void) { // true if empty, false if there's elements
    return dPS2->RVALID & 0b10000000 == 0;
}

void PS2ClearFIFO (void) {
    uint_8 input_byte;
    while (PS2Empty())
        input_byte = dPS2->DATA; // flushes queue
}