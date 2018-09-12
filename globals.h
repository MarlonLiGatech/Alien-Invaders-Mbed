// ============================================
// The header file for general project settings
// Spring 2018 Gatech ECE2035
//=============================================
#ifndef GLOBAL_H
#define GLOBAL_H

// Include all the hardware libraries
#include "mbed.h"
#include "Speaker.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "MMA8452.h"

#define ALIEN_HEIGHT 8
#define ALIEN_WIDTH 11
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define C   0x00B2FF
#define B   0x0000FF
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE
#define G 0xFFD700 //GOLD
#define L 0xD3D3D3 //LIGHT GREY


// Declare the hardware interface objects
extern uLCD_4DGL uLCD;            // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
extern Serial pc;                 // USB Console (tx, rx)
extern MMA8452 acc;        // Accelerometer (sda, sdc, rate)
extern PinDetect button1;                 // Pushbuttons (pin)
extern PinDetect button2;
extern PinDetect button3;
extern AnalogOut DACout;                  // Speaker (pin)
extern PwmOut speaker;
extern DigitalOut myled1;
extern DigitalOut myled2;
extern DigitalOut myled3;
extern Speaker mySpeaker;
extern int alienAlice_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int alienSarah_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int alienJeff_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int ship_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];
extern int missile_sprite[ALIEN_HEIGHT * ALIEN_WIDTH];



#endif //GLOBAL_H