/// TIMER DELAY
/*
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
*/

#include "car_moving.h"

struct timer_t {
       volatile unsigned int status;
       volatile unsigned int control;
       volatile unsigned int periodlo;
       volatile unsigned int periodhi;
       volatile unsigned int snaplo;
       volatile unsigned int snaphi;
};


struct timer_t * const timer = (struct timer_t *) 0xFF202000;

#define TIMERSEC 100000000

void
waitasec(int pow_fraction) {
	   unsigned int t = TIMERSEC >> pow_fraction;
       timer->control = 0x8; // stop the timer
       timer->status = 0; // reset TO
       timer->periodlo = (t & 0x0000FFFF);
       timer->periodhi = (t & 0xFFFF0000) >> 16;
       timer->control = 0x4;
       while ((timer->status & 0x1) == 0);
          timer->status = 0; // reset TO
}


// 16x16 sprites as unidimensional arrays :(
// converted from:
// https://opengameart.org/content/chibi-monsters-set-01
// made by ansimuz.com

// grey 0x52AA
// black 0x0000
// red 0xF000
// yellow 0xFEA0
// light yellow 0xFF53
// light blue 0xCF5F
// darker blue 0x9E1B
// green 0x1E86
// light green 0x76E5
// orange 0xFD00
// light grey 0xAD55






struct Obstacle cars[15];

void instantiate_cars(){
		for (int i = 0; i < 16; i++){
			cars[i].car_type = rand() % 5;
			cars[i].yup = i*15 + 15;
			cars[i].xleft = rand() % 320;
		}
}

void sprite_draw(struct fb_t *const fbp, unsigned short sprite[], int x, int y, int size) {
 int sxi, syi;
 int xi, yi;
	if(size == 4){
		for (sxi = 0; sxi < 320; sxi++)
			for (syi = 0; syi < 1; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*320+sxi];
		}
	}
	if(size == 3){
		for (sxi = 0; sxi < 60; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*60+sxi];
		}
	}
	if(size == 2){
		for (sxi = 0; sxi < 40; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*40+sxi];
		}
	}
	if(size == 1){
		for (sxi = 0; sxi < 20; sxi++)
			for (syi = 0; syi < 13; syi++) {
		 	  xi = x + sxi;
		   	  yi = y + syi;
     	 	  fbp->pixels[yi][xi] = sprite[syi*20+sxi];
		}
	}
}

int xn = 320;
int xl = 0;
int yn = 240;

void
sprite_scroll(struct fb_t *const fbp;) {
	int x, y;
	for(int y = 13; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	for(int y = 14; y < 230; y+=15){
		sprite_draw(fbp, lanes, x, y, 4);
	}
	// array to store location, only need x for loop, update locations, etc etc etc
	while (1){
		for (x = 0; x < 500; x += 1){
			for (int i = 0; i < 16; i += 1){
				if (cars[i].car_type == 0){
					sprite_draw(fbp, ttc, cars[i].xleft + x, cars[i].yup, 3);
				} else if (cars[i].car_type == 1){
					sprite_draw(fbp, uber, cars[i].xleft + x, cars[i].yup, 2);
				} else if (cars[i].car_type == 2){
					sprite_draw(fbp, go, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 3){
					sprite_draw(fbp, zum, 320-(cars[i].xleft + x), cars[i].yup, 3);
				} else if (cars[i].car_type == 4){
					sprite_draw(fbp, car, 320-(cars[i].xleft + x), cars[i].yup, 2);
				}
				
			}
		}
		solid_color(fbp, 0x0000);
			int x;
			int y;
			for(int y = 13; y < 230; y+=15){
				sprite_draw(fbp, lanes, x, y, 4);
			}
			for(int y = 14; y < 230; y+=15){
				sprite_draw(fbp, lanes, x, y, 4);
			}
	}
	
}


void solid_color(struct fb_t *const fbp, unsigned short color) {
    int x, y;
	for (x = 0; x < xn; x++)
       for (y = 0; y < yn; y++) 
          fbp->pixels[y][x] = color; // set pixel value at x,y
}

/*
int
main() {
	
  solid_color(fbp, 0x0000); // make all pixels white
  instantiate_cars();
  sprite_scroll(fbp);
}
*/
