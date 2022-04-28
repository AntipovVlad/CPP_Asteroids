#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"

class Ship : public BaseObject {
private:
    const float r = 15.f;
    bool safe_mode = false;
    bool destroyed = false;
    int hp = 3;
public:
    Ship(float W, float H);

    void move(float dt);
    void rotate(float dt, bool left);
    void destroy_ship();
    void respawn_ship();
    void change_safe_mode();

    bool is_destroyed() const;
    bool is_alive() const;
    bool is_safe() const;

    int get_hp() const;
    float get_angle() const;
};


#endif //ASTEROIDS_SHIP_H
