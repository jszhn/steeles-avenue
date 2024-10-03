#include "audio.h"

#include "../assets/zigzagoon.c"
#include "../assets/trombone.c"
#include "../assets/next_sound.c"

#include "other_devices.h"
#include "other_devices.c"

AUDIO_t *const dAudio = (AUDIO_t*) AUDIO_BASE;

void PlayAudio (const int track_num) {
    const int* track;
    uint_32 track_len;
    switch (track_num) { // sets local variables of interest
        case (1):
            track = zigzagoon;
            track_len = zigzagoon_size;
            break;
        case (2):
            track = trombone;
            track_len = trombone_size;
            break;
        case (3):
            track = next_sound;
            track_len = next_sound_size;
            break;
        default: return;
    }

    for (int i = 0; i < track_len; i++) { // iterates through audio array
        while (dAudio->WSRC == 0 || dAudio->WSLC == 0); // ensures FIFO has space before continuing
        if (dAudio->WSRC > 0 && dAudio->WSLC > 0) { // if audio FIFO has space
            dAudio->LDATA = track[i];
            dAudio->RDATA = track[i];
        }
    }
}
