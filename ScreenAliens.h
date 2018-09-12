#ifndef SCREENALIENS_H
#define SCREENALIENS_H

class ScreenAliens
{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    int get_alien_x_pos() {
        return alien_x_pos;
    }
    int get_alien_y_pos() {
        return alien_y_pos;
    }
    void set_dead() {
        alive = false;
        uLCD.filled_rectangle(alien_x_pos, alien_y_pos, alien_x_pos + ALIEN_WIDTH, alien_y_pos + ALIEN_HEIGHT, _);
        alien_count--;
        alien_x_pos = 0;
        alien_y_pos = 0;
        pc.printf("set dead\r\n");
    }
    static int alien_count;
protected:
    int alien_x_pos;
    int alien_y_pos;
    int alien_dir;  //left = 0, right = 1;
    int move_dist;
    int alive;
};

#endif // GRAPHICS_H