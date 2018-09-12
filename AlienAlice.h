#ifndef ALIENALICE_H
#define ALIENALICE_H
#include "ScreenAliens.h"

class AlienAlice: public ScreenAliens
{
public:
    AlienAlice(int _alien_y_pos);
    void draw();
    void update();
};

#endif // GRAPHICS_H