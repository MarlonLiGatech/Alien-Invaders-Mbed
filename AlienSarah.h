#ifndef ALIENSARAH_H
#define ALIENSARAH_H
#include "ScreenAliens.h"

class AlienSarah: public ScreenAliens
{
public:
    AlienSarah(int _alien_y_pos);
    void draw();
    void update();
};

#endif // GRAPHICS_H