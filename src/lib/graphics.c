#include "graphics.h"
#include "../assets/start_screen.c"
#include "../assets/end_screen.c"

PIXEL_t *const dPixelBuffer = (PIXEL_t*) PIXEL_BUF_CTRL_BASE;

struct fb_t {
    unsigned short volatile pixels[256][512];
};

struct fb_t *const fbp = ((struct fb_t *) 0x8000000);
short int buffer[Y_MAX][X_MAX + 192]; // 240 rows, 512 columns

void PlotSpriteAtColRow (const uint_8 row, const uint_8 col) {
    // currently only plots a single pixel at a time
    if (row >= ROW_MAX || col >= COL_MAX) // if invalid row/col
        return;

    uint_32 x = col * COL_WIDTH;
    uint_32 y = row * ROW_HEIGHT;
    PlotPixel(x, y, BLACK);
}

static void Swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

uint_16 RGBtoColour (uint_8 red, uint_8 green, uint_8 blue) {
    return (blue | (green << 5) | (red << 11));
}

void PlotPixel (uint_32 x, uint_32 y, short int line_colour) {
    volatile short int *one_pixel_address = &buffer[x][y];
    *one_pixel_address = line_colour;
}

void ClearScreen (void) {
    dPixelBuffer->BACK_BUFFER = (int) fbp;
    for (int y = 0; y < Y_MAX; y++) // iterate through each pixel
        for (int x = 0; x < X_MAX; x++)
            PlotPixel(x, y, WHITE);
    dPixelBuffer->BUFFER = 0x1; // swaps buffers
}

void WaitForVSync (void) {
    unsigned int status;
    dPixelBuffer->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = dPixelBuffer->STATUS; // read the status register
    while (status & 0x1) // polling loop waiting for S bit to go to 0
        status = dPixelBuffer->STATUS;
    // exits when refresh done
}

void DrawCanvas (const int canvas_number) {
    uint_16** canvas;
    switch (canvas_number) {
        case (1):
            canvas = start_screen;
            break;
        case (2):
            canvas = end_screen;
            break;
        default: return; // should never happen
    }

    for (int x = 0; x < X_MAX; x++) {
        for (int y = 0; y < Y_MAX; y++) {
            fbp->pixels[y][x] = canvas[x][y];
        }
    }
}

int main (void) {
    // gcc -save-temps -CC -S src/lib/graphics.c
    ClearScreen();
    DrawCanvas(1);
    WaitForVSync();
    for (;;);
}