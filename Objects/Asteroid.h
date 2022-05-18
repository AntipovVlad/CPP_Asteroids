#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "BaseObject.h"

/**
 * @brief Game object Asteroid class
 */
class Asteroid : public BaseObject {
private:
    float vx; //!< x vector coordinate
    float vy; //!< y vector coordinate
    bool valid = true; //!< does asteroid exist
    int hp; //!< current asteroid's hp
    int hp_size; //!< max asteroid's hp
public:
    /**
     * @brief Default constructor
     * @param W width of screen
     * @param H height of screen
     */
    Asteroid(float W, float H);

    /**
     * @brief Constructor for asteroids appeared from splitting
     * @param W width of screen
     * @param H height of screen
     * @param en_x start x coordinate
     * @param en_y start y coordinate
     * @param max_health max heath of asteroid
     */
    Asteroid(float W, float H, float en_x, float en_y, int max_health);

    /**
     * @brief Asteroid move func
     * @param dt Time from last frame
     */
    void move(float dt);

    /**
     * @brief Asteroid rotation func
     * @param dt Time from last frame
     */
    void rotate(float dt);

    /**
     * @brief Asteroid self-destruction func
     */
    void make_invalid();

    /**
     * @brief Asteroid hp decrease func
     */
    void gain_damage();

    /**
     * @brief Checks whether asteroid has hp or not
     * @return param *valid*
     */
    bool is_valid() const;

    /**
     * @brief Returns asteroid's hp
     * @return param *hp*
     */
    int get_hp() const;

    /**
     * @brief Returns max asteroid's hp
     * @return param *hp_size*
     */
    int get_hp_size() const;
};


#endif //ASTEROIDS_ASTEROID_H
