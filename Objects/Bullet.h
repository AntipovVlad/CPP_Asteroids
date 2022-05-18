#ifndef ASTEROIDS_BULLET_H
#define ASTEROIDS_BULLET_H

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


#endif //ASTEROIDS_BULLET_H
