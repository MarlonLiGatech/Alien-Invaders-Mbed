#include "globals.h"
#include "AlienBob.h"
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE
//#include "graphics.h"

AlienBob::AlienBob(int _alien_y_pos)
{
    alien_y_pos = _alien_y_pos;
    alien_x_pos = rand() % 109 + 9;
    alien_dir = rand() % 2;
    move_dist = rand() % 10 + 1;
    phase = 1;
    alive = 1;
}

void AlienBob::draw()
{
    uLCD.filled_rectangle(alien_x_pos, alien_y_pos, alien_x_pos + ALIEN_WIDTH, alien_y_pos + ALIEN_HEIGHT, _);
    if(alive && alien_dir) {     //move right
        if((alien_x_pos + ALIEN_WIDTH) < 127 - move_dist) {
            alien_x_pos += move_dist;
            if(phase) {
                uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobUp_sprite);
            } else {
                uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobDown_sprite);
            }
        } else {
            alien_dir = !alien_dir;
        }
    } else if(alive) {        //move left
        if(alien_x_pos > move_dist) {
            alien_x_pos -= move_dist;
            if(phase) {
                uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobUp_sprite);
            } else {
                uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobDown_sprite);
            }
        } else {
            alien_dir = !alien_dir;
        }
    }
}

void AlienBob::update()
{
    if(alive) {phase = !phase;}
}


