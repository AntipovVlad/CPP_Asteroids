#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float W, float H, vector<float> xy, float en_v) : BaseObject(W, H) {
    x = std::signbit(std::cos(en_v)) ? xy[0] + 2.f : xy[0] - 2.f;
    y = !std::signbit(std::cos(en_v)) ? xy[1] + 2.f : xy[1] - 2.f;

    vx = std::sin(en_v) * 400;
    vy = std::cos(en_v) * 400;
}

void Bullet::move(float dt) {
    y -= dt * vy;
    x += dt * vx;
}

bool Bullet::is_valid() {
    return !(x < 0 || y < 0 || x > w || y > h || !valid);
}

void Bullet::make_invalid() {
    valid = false;
}

Bullet & Bullet::operator=(Bullet &b) {
    if (this != &b) {
        BaseObject::operator=(b);
        vx = b.vx;
        vy = b.vy;
        valid = b.valid;
    }

    return *this;
}

Bullet & Bullet::operator=(Bullet &&b)  noexcept {
    if (this != &b) {
        BaseObject::operator=(b);
        vx = b.vx;
        vy = b.vy;
        valid = b.valid;
    }

    return *this;
}