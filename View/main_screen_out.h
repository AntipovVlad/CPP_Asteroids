#ifndef ASTEROIDS_MAIN_SCREEN_OUT_H
#define ASTEROIDS_MAIN_SCREEN_OUT_H

#include <vector>
#include "../Objects/Bullet.h"
#include "../Objects/Asteroid.h"
#include "../Objects/Ship.h"
#include <SFML/Graphics.hpp>
#include <set>

using std::vector;

/**
 * Draw objects
 *
 * @param win game window
 * @param obj Game object (asteroid or ship)
 */
void draw_object(sf::RenderWindow &win, BaseObject& obj);

/**
 * Draw bullets
 *
 * @param win game window
 * @param obj Game object (asteroid or ship)
 */
void draw_bullet(sf::RenderWindow &win, Bullet& obj);


#endif //ASTEROIDS_MAIN_SCREEN_OUT_H
