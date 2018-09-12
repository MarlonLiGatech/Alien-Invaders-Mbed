#include "globals.h"
#include "AlienSarah.h"

AlienSarah::AlienSarah(int _alien_y_pos)
{
    alien_y_pos = _alien_y_pos;
    alien_x_pos = rand() % 109 + 9;
    alien_dir = rand() % 2;
    move_dist = rand() % 10 + 1;
    alive = 1;
}

void AlienSarah::draw()
{
    uLCD.filled_rectangle(alien_x_pos, alien_y_pos, alien_x_pos + ALIEN_WIDTH, alien_y_pos + ALIEN_HEIGHT, _);
    if(alive && alien_dir) {     //move right
        if((alien_x_pos + ALIEN_WIDTH) < 127 - move_dist) {
            alien_x_pos += move_dist;
            uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienSarah_sprite);
        } else {
            alien_dir = !alien_dir;
        }
    } else if(alive) {        //move left
        if(alien_x_pos > move_dist) {
            alien_x_pos -= move_dist;
            uLCD.BLIT(alien_x_pos, alien_y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienSarah_sprite);
        } else {
            alien_dir = !alien_dir;
        }
    }
}

void AlienSarah::update()
{

}