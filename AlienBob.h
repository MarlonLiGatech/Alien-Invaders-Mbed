#include "ScreenAliens.h"

class AlienBob: public ScreenAliens
{
public:
    AlienBob(int _alien_y_pos);
    void draw();
    void update();
private:
    int phase;  //up = 1, down = 0;
};
