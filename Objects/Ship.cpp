#include "Ship.h"
#include "BaseObject.h"
#include <cmath>
#include <iostream>

Ship::Ship(float w, float h) : BaseObject(w, h) {
    x = w / 2;
    y = h / 2;
    size = 4;
    speed = 256.f;
    dangle = 4.f;

    dots = {
        {0.f, -2.25f},
        {1.f, 0.75f},
        {-1.f, 0.75f}
    };

    for (auto &d : dots)
        for (auto &dd : d)
            dd *= r;
}

void Ship::move(float dt) {
    y -= dt * speed * std::cos(angle);
    x += dt * speed * std::sin(angle);

    if (y < 0) y += h;
    else if (y > h) y -= h;

    if (x < 0) x += w;
    else if (x > w) x -= w;
}

void Ship::rotate(float dt, bool left) {
    if (left) angle -= dt * dangle;
    else angle += dt * dangle;

    if (angle > M_PI * 2) angle -= M_PI * 2;
    if (angle < M_PI * -2) angle += M_PI * 2;
}

void Ship::destroy_ship() {
    hp -= 1;
    destroyed = true;
}

bool Ship::is_alive() const {
    return hp != 0;
}

bool Ship::is_destroyed() const {
    return destroyed;
}

void Ship::respawn_ship() {
    destroyed = false;
    x = w / 2;
    y = h / 2;
}

void Ship::change_safe_mode() {
    safe_mode = !safe_mode;
}

bool Ship::is_safe() const {
    return safe_mode;
}

int Ship::get_hp() const {
    return hp;
}

float Ship::get_angle() const {
    return angle;
}
