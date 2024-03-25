//
// Interfaces with other devices on the DE1-SoC not covered by other files.
//

#ifndef OTHER_DEVICES_H
#define OTHER_DEVICES_H

#include "device_structs.h"
#include "hardware_constants.h"

void WriteLEDSingle (uint_8 integer_write_value);
void WriteHexDisplayFull (uint_32 write_value);
static void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value);
static uint_8 NumberToHexBinary (uint_8 write_value);
void ClearHex (void);

// timer utility functions
int SecondsToTicks (double seconds);
void SetTimer (unsigned int ticks);

#endif
