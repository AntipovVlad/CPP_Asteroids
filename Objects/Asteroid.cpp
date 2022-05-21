#include "Asteroid.h"
#include <random>
#include <cmath>

Asteroid::Asteroid(float W, float H): BaseObject(W, H) {
    size = 7;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr_1(0, 600);
    std::uniform_real_distribution<float> distr_2(0, 800);
    std::uniform_real_distribution<float> distr_3(0.8, 1.2);
    std::uniform_real_distribution<float> distr_4(-10, 10);
    std::uniform_real_distribution<float> distr_5(-320, 320);
    std::uniform_real_distribution<float> distr_6(-2, 2);
    std::uniform_real_distribution<float> distr_7(1, 4);

    x = distr_2(eng);
    y = distr_1(eng);
    vx = distr_5(eng);
    vy = distr_5(eng);
    dangle = distr_6(eng);
    hp = (int)distr_7(eng);
    hp_size = hp < 4 ? hp : 3;

    dots = {
        {0.f, -16.f},
        {8.f * (float)std::sqrt(3), -8.f},
        {8.f * (float)std::sqrt(3), 8.f},
        {0.f, 16.f},
        {-8.f * (float)std::sqrt(3), 8.f},
        {-8.f * (float)std::sqrt(3), -8.f},
    };

    for (auto &d : dots)
        for (auto &dd : d)
            dd = (float)hp_size * dd * distr_3(eng) + distr_4(eng);
}

Asteroid::Asteroid(float W, float H, float en_x, float en_y, int max_health) : Asteroid(W, H) {
    size = 7;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr_3(0.8, 1.2);
    std::uniform_real_distribution<float> distr_4(-10, 10);

    x = en_x;
    y = en_y;
    hp = max_health;
    hp_size = max_health;

    dots = {
            {0.f, -16.f},
            {8.f * (float)std::sqrt(3), -8.f},
            {8.f * (float)std::sqrt(3), 8.f},
            {0.f, 16.f},
            {-8.f * (float)std::sqrt(3), 8.f},
            {-8.f * (float)std::sqrt(3), -8.f},
    };

    for (auto &d : dots)
        for (auto &dd : d)
            dd = (float)hp_size * dd * distr_3(eng) + distr_4(eng);
}

void Asteroid::move(float dt) {
    y -= dt * vy;
    x += dt * vx;

    if (y < 0) y += h;
    else if (y > h) y -= h;

    if (x < 0) x += w;
    else if (x > w) x -= w;
}

void Asteroid::rotate(float dt) {
    angle += dt * dangle;
}

void Asteroid::make_invalid() {
    valid = false;
}

void Asteroid::gain_damage() {
    hp -= 1;
}

bool Asteroid::is_valid() const {
    return valid;
}

int Asteroid::get_hp() const {
    return hp;
}

int Asteroid::get_hp_size() const {
    return hp_size;
}

Asteroid& Asteroid::operator=(Asteroid &ast) {
    if (this != &ast) {
        BaseObject::operator=(ast);
        vx = ast.vx;
        vy = ast.vy;
        hp = ast.hp;
        hp_size = ast.hp_size;
        valid = ast.valid;
    }

    return *this;
}

Asteroid & Asteroid::operator=(Asteroid &&ast)  noexcept {
    if (this != &ast) {
        BaseObject::operator=(ast);
        vx = ast.vx;
        vy = ast.vy;
        hp = ast.hp;
        hp_size = ast.hp_size;
        valid = ast.valid;
    }

    return *this;
}
