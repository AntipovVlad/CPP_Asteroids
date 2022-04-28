#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H
#include "BaseObject.h"

class Bullet : public BaseObject {
private:
    float vx;
    float vy;
    bool valid = true;
public:
    Bullet(float W, float H, vector<float> xy, float en_v);

    void move(float dt);
    void make_invalid();

    bool is_valid();
};


#endif //ASTEROIDS_BULLET_H
