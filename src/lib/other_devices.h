#ifndef STEELES_AVENUE_OTHER_DEVICES_H
#define STEELES_AVENUE_OTHER_DEVICES_H

#include "device_structs.h"
#include "hardware_constants.h"

void WriteLEDFull(uint_8 write_val);
void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value);
void WriteHexDisplayFull (uint_32 write_value);
static uint_8 NumberToHexBinary (uint_8 write_value);

int SecondsToTicks (double seconds);
void SetTimer (unsigned int ticks);
uint_32 TimerDone (void);

#endif //STEELES_AVENUE_OTHER_DEVICES_H
