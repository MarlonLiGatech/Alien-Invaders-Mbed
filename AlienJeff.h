#ifndef ALIENJEFF_H
#define ALIENJEFF_H
#include "ScreenAliens.h"

class AlienJeff: public ScreenAliens
{
public:
    AlienJeff(int _alien_y_pos);
    void draw();
    void update();
};

#endif // GRAPHICS_H