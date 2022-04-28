#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H
#include "BaseObject.h"

class Asteroid : public BaseObject {
private:
    float vx;
    float vy;
    bool valid = true;
    int hp;
    int hp_size;
public:
    Asteroid(float W, float H);
    Asteroid(float W, float H, float en_x, float en_y, int s);

    void move(float dt);
    void rotate(float dt);
    void make_invalid();
    void gain_damage();

    bool is_valid() const;
    int get_hp() const;
    int get_hp_size() const;
};


#endif //ASTEROIDS_ASTEROID_H
