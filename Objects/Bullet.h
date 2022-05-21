#pragma once

#include "BaseObject.h"

/**
 * @brief Game object Bullet class
 */
class Bullet : public BaseObject {
private:
    float vx; //!< x vector coordinate
    float vy; //!< y vector coordinate
    bool valid = true; //!< does asteroid exist
public:
    /**
     * @brief Default constructor
     * @param W width of screen
     * @param H height of screen
     * @param xy x and y coordinates
     * @param en_v direction vector
     */
    Bullet(float W, float H, vector<float> xy, float en_v);

    Bullet(Bullet & b) : BaseObject(b), vx(b.vx), vy(b.vy), valid(b.valid) {}
    Bullet(Bullet && b) noexcept : BaseObject(b), vx(b.vx), vy(b.vy), valid(b.valid) {}
    Bullet& operator=(Bullet & ast);
    Bullet& operator=(Bullet && ast) noexcept;
    ~Bullet() = default;

    /**
     * @brief Bullet move func
     * @param dt Time from last frame
     */
    void move(float dt);

    /**
     * @brief Asteroid self-destruction func
     */
    void make_invalid();

    /**
     * @brief Checks whether asteroid has hp or not
     * @return param *valid*
     */
    bool is_valid();
};
