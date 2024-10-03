/*
 *  Steeles Avenue
 */

// C standard libary
#include <stdlib.h>

// header definitions
#include "lib/address_map_nios2.h"
#include "lib/device_structs.h"
#include "lib/ps2.h"
#include "lib/audio.h"
#include "lib/hardware_constants.h"

// game assets
#include "assets/start_screen.c"
#include "assets/end_screen.c"
#include "assets/vehicles.c"

struct Obstacle {
    int car_type;
    int xleft;
    int xright;
    int yup;
    int ydown;
	int diff;
};

/*
 * Board device pointers
 */
struct fb_t *const fbp = ((struct fb_t *) 0x8000000);
struct timer_t *const timer = (struct timer_t *) 0xFF202000;
TIMER_t *const dTimer = (TIMER_t*) TIMER_BASE;
TIMER_t *const dTimer2 = (TIMER_t*) TIMER_2_BASE;
vuint_32 *const dLEDs = (vuint_32*) LEDR_BASE;
vuint_32 *const dHEX30 = (vuint_32*) HEX3_HEX0_BASE;
vuint_32 *const dHEX74 = (vuint_32*) HEX5_HEX4_BASE;
PIXEL_t *const dPixelBuffer = (PIXEL_t *) PIXEL_BUF_CTRL_BASE;

int xn = 320;
int xl = 0;
int yn = 240;
struct Obstacle cars[13];

/*
 * Function definitions
 */

static void GameLoop(void);
static void StartScreen(void);
static void EndScreen(void);

void WriteLEDFull(uint_8 write_val);
void WriteHexDisplaySingle (uint_8 display_num, uint_32 write_value);
void WriteHexDisplayFull (uint_32 write_value);
static uint_8 NumberToHexBinary (uint_8 write_value);

int SecondsToTicks (double seconds);
void SetTimer (unsigned int ticks);
uint_32 TimerDone (void);

void WaitForVSync(void);

void GetUserControl(int *x_movement, int *y_movement);

void waitasec(int pow_fraction);

void instantiate_cars();

void sprite_draw(struct fb_t *const fbp, unsigned short sprite[], int x, int y, int size);
void sprite_draw_2d(struct fb_t *const fbp, int cavna, int x, int y, int size);

void sprite_scroll(struct fb_t *const fbp);

void solid_color(struct fb_t *const fbp, unsigned short color);

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



void waitasec(int pow_fraction) {
    unsigned int t = TIMER_SEC >> pow_fraction;
    timer->control = 0x8; // stop the timer
    timer->status = 0; // reset TO
    timer->periodlo = (t & 0x0000FFFF);
    timer->periodhi = (t & 0xFFFF0000) >> 16;
    timer->control = 0x4;
    while ((timer->status & 0x1) == 0);
    timer->status = 0; // reset TO
}

void PollTimer (uint_32 const ticks) {
    SetTimer(ticks);
    while (TimerDone() == 0);
    dTimer2->STATUS = 0;
}

int num_buses;
void instantiate_cars() {
    num_buses = 0;
    for (int i = 0; i < 13; i++) {
        cars[i].car_type = rand() % 5;
        cars[i].yup = i * ROW_HEIGHT + 15;
        cars[i].ydown = i * ROW_HEIGHT + 30;
        cars[i].xleft = rand() % 320;
        if (cars[i].car_type == 0 || cars[i].car_type == 2 || cars[i].car_type == 3) {
            cars[i].xright = cars[i].xleft + 60;
            num_buses += 1;
        }
        if (cars[i].car_type == 1 || cars[i].car_type == 4) {
            cars[i].xright = cars[i].xleft + 40;
        }
		cars[i].diff = (320-cars[i].xleft);
    }
}

void sprite_draw_2d(struct fb_t *const fbp, int canvas_number, int x, int y, int size) {
    unsigned short* sprite; // local var
    if (canvas_number == 1) sprite = start_screen;
    else sprite = end_screen;

    int sxi, syi;
    int xi, yi;
	if (size == 5) {
        for (sxi = 0; sxi < 320; sxi++)
            for (syi = 0; syi < 240; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 320 + sxi];
            }
    }
}

void sprite_draw(struct fb_t *const fbp, unsigned short sprite[], int x, int y, int size) {
    int sxi, syi;
    int xi, yi;
	if (size == 5) {
        for (sxi = 0; sxi < 320; sxi++)
            for (syi = 0; syi < 240; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 320 + sxi];
            }
    }
    if (size == 4) {
        for (sxi = 0; sxi < 320; sxi++)
            for (syi = 0; syi < 1; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 320 + sxi];
            }
    }
    if (size == 3) {
        for (sxi = 0; sxi < 60; sxi++)
            for (syi = 0; syi < 13; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 60 + sxi];
            }
    }
    if (size == 2) {
        for (sxi = 0; sxi < 40; sxi++)
            for (syi = 0; syi < 13; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 40 + sxi];
            }
    }
    if (size == 1) {
        for (sxi = 0; sxi < 20; sxi++)
            for (syi = 0; syi < 13; syi++) {
                xi = x + sxi;
                yi = y + syi;
                fbp->pixels[yi][xi] = sprite[syi * 20 + sxi];
            }
    }
}

void solid_color(struct fb_t *const fbp, unsigned short color) {
    int x, y;
    for (x = 0; x < xn; x++)
        for (y = 0; y < yn; y++)
            fbp->pixels[y][x] = color; // set pixel value at x,y
}

static void GameLoop(void) {
    int x;
	
    // draw lanes
    for (int y = 28; y < 200; y += 15) {
        sprite_draw(fbp, lanes, x, y, 4);
    }
    for (int y = 29; y < 200; y += 15) {
        sprite_draw(fbp, lanes, x, y, 4);
    }


    // define some initial game parameters
    int x_position = 8, y_position = 14;
    int x_delta = 0, y_delta = 0;
    uint_8 iterations = 0, lives = 5, game_over = 0;
    uint_32 score = 0;

    uint_8 nu = 0;
    // primary game loop; continues until game_over is true
    while (game_over == 0) {
        int x;
        // draw bus/car sprites
		
        for (x = 0; x < 320; x += 1) {
            // PollTimer(SecondsToTicks(1/60));
            //for (int p = 0; p < 1000000; p++);
			for (int i = 0; i < 13; i += 1){
				int xt = x_position * COL_WIDTH; // temporary variables for comparisons
				if ((cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
                
				
				if (cars[i].car_type == 0 || cars[i].car_type == 1){
					
					if ((cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 20) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 20) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
					if ((cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 40) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 40) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
				}
				if (cars[i].car_type == 0){
					if ((cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 60) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 60) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
				}
				
				if (cars[i].car_type == 2 || cars[i].car_type == 3 || cars[i].car_type == 4){
					if ((320 - cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 20) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 20) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
					if ((320 - cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 40) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 40) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
					if ((320 - cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 60) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 60) == xt){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
				}
				if (cars[i].car_type == 2 || cars[i].car_type == 3){
					if ((320 - cars[i].xleft + x) < 320){
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((cars[i].xleft + x + 80) < xt && xt < (cars[i].xleft + x) ){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
						}
                    }
				} else {
					if (cars[i].yup == y_position * ROW_HEIGHT) {
						if ((x - cars[i].diff + 80) < xt && xt < (x - cars[i].diff)){ 
                            x_position = COL_MAX / 2 + 1;
                            y_position = ROW_MAX - 1;
                            solid_color(fbp, 0x0000);
                            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
                            lives--;
                    }
					}
					}
				}
				

                for (int y = 28; y < 200; y += 15) {
                    sprite_draw(fbp, lanes, 0, y, 4);
                }
                for (int y = 29; y < 200; y += 15) {
                    sprite_draw(fbp, lanes, 0, y, 4);
                }
				
				
				if (cars[i].car_type == 0) {
                    if ((cars[i].xleft + x) > 320){
                    	sprite_draw(fbp, ttc, (x - cars[i].diff), cars[i].yup, 3);
					} else {
						sprite_draw(fbp, ttc, (cars[i].xleft + x), cars[i].yup, 3);
					}
                } else if (cars[i].car_type == 1) {
					if ((cars[i].xleft + x) > 320){
                    	sprite_draw(fbp, uber, (x - cars[i].diff), cars[i].yup, 2);
					} else {
						sprite_draw(fbp, uber, (cars[i].xleft + x), cars[i].yup, 2);
					}
                } else if (cars[i].car_type == 2) {
					if ((cars[i].xleft + x) > 320){
                    	sprite_draw(fbp, go, 260 - (x - cars[i].diff), cars[i].yup, 3);
					} else {
						sprite_draw(fbp, go, 260 - (cars[i].xleft + x), cars[i].yup, 3);
					}
                } else if (cars[i].car_type == 3) {
					if ((cars[i].xleft + x) > 320){
                    	sprite_draw(fbp, zum, 260 - (x - cars[i].diff), cars[i].yup, 3);
					} else {
						sprite_draw(fbp, zum, 260 - (cars[i].xleft + x), cars[i].yup, 3);
					}
                } else if (cars[i].car_type == 4) {
					if ((cars[i].xleft + x) > 320){
                    	sprite_draw(fbp, car, 260 - (x - cars[i].diff), cars[i].yup, 2);
					} else {
						sprite_draw(fbp, car, 260 - (cars[i].xleft + x), cars[i].yup, 2);
					}
                }
				
            }
			if (lives == 0) { // ends game when no lives left
                game_over = 1;
                goto end;
            }

            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);
            GetUserControl(&x_delta, &y_delta);
            if (x_delta == 0 && y_delta == 0) continue; // if no change in position, continue
            // clear previous position
            sprite_draw(fbp, black_box, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);

            // player bound checking
            int time_bonus = 0;
            if ((x_position + x_delta) * COL_WIDTH >= X_MAX) x_position = 0;
            else if ((x_position + x_delta) * COL_WIDTH < 0) x_position = X_MAX / COL_WIDTH - 1;
            if ((y_position + y_delta) * ROW_HEIGHT >= Y_MAX) y_position = Y_MAX - 1;
            else if ((y_position + y_delta) * ROW_HEIGHT < 0) {
                y_position = Y_MAX / ROW_HEIGHT - 1;
                iterations++;
                nu = 0x1;
                time_bonus = TimerDone();
                SetTimer(SecondsToTicks(5));
            }

            // update position
            x_position += x_delta;
            y_position += y_delta;
            if (y_delta != 0) score++;
            // draw raccoon at new position
            sprite_draw(fbp, raccoon, x_position * COL_WIDTH, y_position * ROW_HEIGHT, 1);

            // reset variables to prepare for next loop
            WaitForVSync();
            x_delta = 0;
            y_delta = 0;

            if (nu & 0x1) {
                score += num_buses + (time_bonus * time_bonus * 9) + iterations * 3;
                nu = 0;
            }
            WriteHexDisplayFull(score);
            WriteLEDFull(lives);
		}

            
        
        // if raccoon has reached the top
    }
    end: return;
}

static void StartScreen(void) {
    sprite_draw_2d(fbp, 1, 0, 0, 5);
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
    PlayAudio(3);
    solid_color(fbp, BLACK);
}

static void EndScreen(void) {
    sprite_draw_2d(fbp, 2, 0, 0, 5);
    PlayAudio(2);
    PS2PollforChar('\n'); // checks for 'enter' key
    PS2ClearFIFO();
    PlayAudio(3);
}

void WaitForVSync(void) {
    unsigned int status;
    dPixelBuffer->BUFFER = 1; // start the synchronization process; write 1 into front buffer addr register
    status = dPixelBuffer->STATUS; // read the status register
    while (status & 0x1) // polling loop waiting for S bit to go to 0
        status = dPixelBuffer->STATUS;
    // exits when refresh done
}

int main() {
    // set-up functions upon system start
    PS2ClearFIFO();
    WriteHexDisplayFull(0);
    solid_color(fbp, 0xFFFF); // make all pixels white
    instantiate_cars();

	while (1) { // primary game loop
        StartScreen();
        GameLoop();
        EndScreen();
    }
}
