#include "other_devices.h"

TIMER_t *const dTimer = (TIMER_t*) TIMER_BASE;
TIMER_t *const dTimer2 = (TIMER_t*) TIMER_2_BASE;
vuint_32 *const dLEDs = (vuint_32*) LEDR_BASE;
vuint_32 *const dHEX30 = (vuint_32*) HEX3_HEX0_BASE;
vuint_32 *const dHEX74 = (vuint_32*) HEX5_HEX4_BASE;

void WriteLEDFull (uint_8 write_val) {
    if (write_val > 10) write_val = 10;
    int bin_val = 1;

    for (int i = 0; i < write_val; i++) {
        bin_val <<= 1;
        bin_val++;
    }
    *dLEDs = bin_val;
}

void WriteHexDisplayFull (uint_32 write_value) {
    uint_32 count = 0;
    while (count <= 7) { // iterates through each display
        WriteHexDisplaySingle(count, write_value % 16);
        write_value /= 16; // updates value
        count++;
    }
}

void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value) {
    // display num ranges from 0-7
    write_value = write_value & 0b11111111; // truncate write value to ensure no interference
    vuint_32* display_addr;

    if (display_num > 3) {
        display_addr = dHEX74;
        display_num -= 4;
    } else
        display_addr = dHEX30;

    write_value = NumberToHexBinary(write_value);
    uint_32 temp = *display_addr & (ONES ^ (0b11111111 << (display_num * 8))); // selectively clears a single display
    *display_addr = temp | (write_value << (display_num * 8)); // writes to HEX display
}

static uint_8 NumberToHexBinary (uint_8 write_value) {
    switch (write_value) {
        case 1: return 0b0000110;
        case 2: return 0b1011011;
        case 3: return 0b1001111;
        case 4: return 0b1100110;
        case 5: return 0b1101101;
        case 6: return 0b1111101;
        case 7: return 0b0000111;
        case 8: return 0b1111111;
        case 9: return 0b1101111;
        case 10: return 0b1110111; // A
        case 11: return 0b1111100; // B
        case 12: return 0b0111001; // C
        case 13: return 0b1011110; // D
        case 14: return 0b1111001; // E
        case 15: return 0b1110001; // F
        default: return 0b0111111; // 0
    }
}

inline int SecondsToTicks (double const seconds) {
    return (int) (seconds * TIMER_SEC);
}

void SetTimer (unsigned int const ticks) {
    dTimer2->STATUS = 0x0; // reset status bit
    dTimer2->CTRL = 0x8; // stop, cont bits
    dTimer2->COUNTER_START_LOW = ticks & 0xFFFF;
    dTimer2->COUNTER_START_HIGH = (ticks >> 16) & 0xFFFF;
    dTimer2->CTRL = 0x4; // start, cont bits
}

inline uint_32 TimerDone (void) { // 1: done, 0: not done
    return (dTimer2->STATUS & 0x1);
}