#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include <SFML/Graphics.hpp>
#include "BaseObject.h"

/**
 * @brief Game object Ship class
 */
class Ship : public BaseObject {
private:
    bool safe_mode = false; //!< can asteroid be destroyed
    bool destroyed = false; //!< does asteroid destroyed
    int hp = 3; //!< ship's hp
public:
    /**
     * @brief Default constructor
     * @param W width of screen
     * @param H height of screen
     */
    Ship(float W, float H);

    /**
     * @brief Ship move func
     * @param dt Time from last frame
     */
    void move(float dt);

    /**
     * @brief Ship rotation func
     * @param dt time from last frame
     * @param left direction of rotation
     */
    void rotate(float dt, bool left);

    /**
     * @brief Ship destruction func
     */
    void destroy_ship();

    /**
     * @brief Ship respawn func
     */
    void respawn_ship();

    /**
     * @brief Ship making ship visible or invisible for asteroids func
     */
    void change_safe_mode();

    /**
     * @brief Returns whether ship destroyed or not
     */
    bool is_destroyed() const;

    /**
     * @brief Returns whether ship has hp or not
     */
    bool is_alive() const;

    /**
     * @brief Returns whether ship in safe mode or not
     */
    bool is_safe() const;

    /**
     * @brief Returns ship hp
     */
    int get_hp() const;

    /**
     * @brief Returns ship angle
     */
    float get_angle() const;
};


#endif //ASTEROIDS_SHIP_H
