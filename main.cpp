// Project includes
#include "globals.h"
#include "AlienBob.h"
#include "AlienAlice.h"
#include "AlienSarah.h"
#include "AlienJeff.h"

// Functions in this file
int main();
void hardware_init();
void exit_game(time_t startTime);
void menu_music();
void missile_music();
void button1_hit_callback (void);
void button2_hit_callback (void);
void button3_hit_callback (void);
void init_player();
void update_player();
void check_missile();
void check_collision(ScreenAliens** aliens);
void check_end(time_t startTime);
void check_acc();
void collision_music();

int ScreenAliens::alien_count = 6;
int alien_num = 6;
int ship_x_pos;
int ship_x_pos_prev;
int ship_update_left;
int ship_update_right;
int missile;
int missile_x_pos;
int missile_y_pos;
struct GameInputs {
    int b1, b2, b3;     // Button presses
    double ax, ay, az;  // Accelerometer readings
} inputs;

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    hardware_init();
    srand((int)time(0));
    pc.printf("after init\r\n");
    ScreenAliens** aliens = new ScreenAliens* [alien_num];
    aliens[0] = new AlienBob(20);
    aliens[1] = new AlienAlice(30);
    aliens[2] = new AlienSarah(40);
    aliens[3] = new AlienBob(50);
    aliens[4] = new AlienJeff(60);
    aliens[5] = new AlienAlice(70);
    pc.printf("before draw\r\n");
    for(int i = 0; i < alien_num; i++) {
        aliens[i]->draw();
    }
    init_player();
    time_t startTime;
    startTime = time(0);
    while(true) {
        check_acc();
        check_collision(aliens);
        for(int i = 0; i < alien_num; i++) {
            aliens[i]->draw();
            aliens[i]->update();
        }
        update_player();
        check_missile();
        check_end(startTime);
    }
}

void hardware_init()
{
    // Crank up the speed
    uLCD.baudrate(57600);
    pc.baud(115200);
    //Initialize pushbuttons
    button1.mode(PullUp);
    button2.mode(PullUp);
    button3.mode(PullUp);
    wait(0.01);
    //Setup Interrupt callback functions for a pb hit
    button1.attach_deasserted(&button1_hit_callback);
    button2.attach_deasserted(&button2_hit_callback);
    button3.attach_deasserted(&button3_hit_callback);
    //Start sampling pb inputs using interrupts
    button1.setSampleFrequency();
    button2.setSampleFrequency();
    button3.setSampleFrequency();
//    if(!acc.isXYZReady()) {
//        wait(0.01);
//    } else {
//        acc.readXYZGravity(&in.ax,&in.ay,&in.az); //notice this is passed by reference use pointers
//    }
}

void init_player()
{
    ship_x_pos = rand() % 109 + 9;
    uLCD.BLIT(ship_x_pos, 110, 11, 8, ship_sprite);
}

void check_acc()
{
    if(!acc.isXYZReady()) {
        wait(0.01);
    } else {
        acc.readXYZGravity(&inputs.ax,&inputs.ay,&inputs.az); //notice this is passed by reference use pointers
    }
    if (inputs.ax < -0.35)
        ship_update_left = true;
    if (inputs.ax > 0.35)
        ship_update_right = true;
}
void update_player()
{
    if(ship_update_left) {
        ship_x_pos_prev = ship_x_pos;
        if(ship_x_pos >= 9)
            ship_x_pos -= 10;
        uLCD.filled_rectangle(ship_x_pos_prev, 110, ship_x_pos_prev+11, 118, _);
        uLCD.BLIT(ship_x_pos, 110, 11, 8, ship_sprite);
        ship_update_left = false;
    } else if(ship_update_right) {
        ship_x_pos_prev = ship_x_pos;
        if(ship_x_pos <= 107)
            ship_x_pos += 10;
        uLCD.filled_rectangle(ship_x_pos_prev, 110, ship_x_pos_prev+11, 118, _);
        uLCD.BLIT(ship_x_pos, 110, 11, 8, ship_sprite);
        ship_update_right = false;
    }
}

void check_missile()
{
    if(missile) {
        if (missile_y_pos < 7) {
            missile = false;
            uLCD.filled_rectangle(missile_x_pos, missile_y_pos, missile_x_pos+11, missile_y_pos + 8, _);
        } else {
            if(missile_y_pos != 110)
                uLCD.filled_rectangle(missile_x_pos, missile_y_pos, missile_x_pos+11, missile_y_pos + 8, _);
            missile_y_pos -= 7;
            uLCD.BLIT(missile_x_pos, missile_y_pos, 11, 8, missile_sprite);
        }
    }
}

void check_collision(ScreenAliens** aliens)
{
    int alien_x, alien_y;
    for(int i = 0; i < alien_num; i++) {
        alien_x = aliens[i]->get_alien_x_pos();
        alien_y = aliens[i]->get_alien_y_pos();
        if (alien_x < missile_x_pos + 11
                && alien_x + 11 > missile_x_pos
                && alien_y < missile_y_pos + 8
                && 8 + alien_y > missile_y_pos) {
            collision_music();
            aliens[i]->set_dead();
            uLCD.filled_rectangle(0, missile_y_pos, 127, missile_y_pos + 8, _);
            missile = false;
        }
    }
}

void check_end(time_t startTime)
{

    if (ScreenAliens::alien_count == 0) {

        exit_game(startTime);
    }
}

void button1_hit_callback (void)   //fire
{
    myled1 = !myled1;
    if(!missile) {
        missile_x_pos = ship_x_pos;
        missile_y_pos = 110;
        missile = true;
        missile_music();
    }
}

void button2_hit_callback (void)   //go right
{
    myled2 = !myled2;
    ship_update_right = true;
}

void button3_hit_callback (void)   //go left
{
    myled3 = !myled3;
    ship_update_left = true;
}

void exit_game(time_t startTime)
{
    time_t endTime = time(0)-startTime;
    uLCD.cls();
    uLCD.printf("\n\n Congratulations!!\n\n Earth Saved!\n\n\n (%d Seconds)",
                endTime);
    menu_music();
    exit(0);
}

void menu_music()
{
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(329.63,1.35,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(349.23,1.35,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(392.00,1.35,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(440.00,1.35,0.1);
}

void missile_music()
{
    mySpeaker.PlayNote(164.81,0.15,0.1);
    mySpeaker.PlayNote(146.83,0.15,0.1);
}

void collision_music()
{
    mySpeaker.PlayNote(100,0.15,0.1);
    mySpeaker.PlayNote(50,0.15,0.1);
}