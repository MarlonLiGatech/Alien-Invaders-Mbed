#include "globals.h"
// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11);             // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
Serial pc(USBTX,USBRX);                 // USB Console (tx, rx)
MMA8452 acc(p28, p27, 100000);        // Accelerometer (sda, sdc, rate)
PinDetect button1(p21);                 // Pushbuttons (pin)
PinDetect button2(p22);
PinDetect button3(p23);
AnalogOut DACout(p18);                  // Speaker (pin)
PwmOut speaker(p26);
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
Speaker mySpeaker(p26);

int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,X,_,_,_,_,_,X,_,_,
    X,_,_,X,_,_,_,X,_,_,X,
    X,_,X,X,X,X,X,X,X,_,X,
    X,X,X,_,X,X,X,_,X,X,X,
    X,X,X,X,X,X,X,X,X,X,X,
    _,_,X,X,X,X,X,X,X,_,_,
    _,_,X,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,X,_,
};

int alienBobDown_sprite[8 * 11] = {
    _,_,X,_,_,_,_,_,X,_,_,
    _,_,_,X,_,_,_,X,_,_,_,
    _,_,X,X,X,X,X,X,X,_,_,
    _,X,X,_,X,X,X,_,X,X,_,
    X,X,X,X,X,X,X,X,X,X,X,
    X,_,X,X,X,X,X,X,X,_,X,
    X,_,X,_,_,_,_,_,X,_,X,
    _,_,_,X,X,_,X,X,_,_,_,
};

int alienAlice_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,_,_,X,X,X,_,_,_,_,
    _,X,X,X,X,X,X,X,X,X,_,
    X,X,X,X,X,X,X,X,X,X,X,
    X,X,X,_,_,X,_,_,X,X,X,
    X,X,X,X,X,X,X,X,X,X,X,
    _,_,_,X,X,_,X,X,_,_,_,
    _,_,X,X,_,_,_,X,X,_,_,
    X,X,_,_,_,X,_,_,_,X,X,
};

int alienSarah_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,_,_,X,X,X,_,_,_,_,
    _,_,_,X,_,X,_,X,_,_,_,
    C,C,_,C,C,C,C,C,_,C,C,
    C,C,C,_,C,C,C,_,C,C,C,
    _,_,C,C,C,C,C,C,C,_,_,
    _,C,C,_,C,_,C,_,C,C,_,
    _,C,_,C,_,_,_,C,_,C,_,
    C,C,_,C,_,_,_,C,_,C,C,
};

int alienJeff_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    X,B,_,C,B,X,B,C,_,B,B,
    B,B,C,_,B,_,B,_,C,B,B,
    _,_,_,B,B,_,B,B,_,_,_,
    B,B,C,B,B,_,B,B,C,B,B,
    B,B,B,_,B,_,B,_,B,B,B,
    _,_,_,B,C,_,C,B,_,_,_,
    _,_,B,B,B,_,B,B,B,_,_,
    _,_,_,B,B,_,B,B,_,_,_,
};

int ship_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,_,_,_,_,_,_,_,_,_,
    _,_,_,G,_,_,_,G,_,_,_,
    _,_,_,G,G,_,G,G,_,_,_,
    _,_,G,G,_,_,_,G,G,_,_,
    _,G,_,G,G,_,G,G,_,G,_,
    G,_,G,G,G,G,G,G,G,_,G,
    _,G,_,G,G,_,G,G,_,G,_,
    _,_,G,G,_,_,_,G,G,_,_,
};

int missile_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
    _,_,_,_,_,X,X,_,_,_,_,
    _,_,_,_,_,X,X,_,_,_,_,
    _,_,_,_,_,X,X,_,_,_,_,
    _,_,_,_,X,X,X,X,_,_,_,
    _,_,_,_,X,X,X,X,_,_,_,
    _,_,_,_,X,X,X,X,_,_,_,
    _,_,_,_,X,X,X,X,_,_,_,
    _,_,_,_,X,_,_,X,_,_,_,
};