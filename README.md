# Steeles Avenue
Frogger-inspired game, built for Terasic's DE1-SoC platform targeting a Nios II instruction architecture.  You play as a raccoon crossing Steeles Avenue, imagined as a 13-lane road. 

The game makes use of VGA for display and a PS/2 keyboard input.

Created by: Yanni Alevras and Jason Zhang

![](src/assets/start_screen.png)

## Installation
*Steeles Avenue* is intended for use with the Terasic DE1-SoC for a Nios II soft-core processor. Any other development platforms or architectures are untested and may not function as intended.

In the Quartus Monitor Program, open the `steeles_avenue.amp` project file. Ensure that the FPGA board has the Nios II system downloaded on.  Press the symbol to compile and load onto the board.

On [CPUlator](https://cpulator.01xz.net/?sys=nios-de1soc), enable a DE1-SoC Nios II system. In the editor, change the language to C, and import the `src/lib/combination.c` file. Press `Compile and Load (F5)`, then `Continue (F3)` to start the game.
