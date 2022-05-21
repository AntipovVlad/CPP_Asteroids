#ifndef ASTEROIDS_MAIN_FUNCS_H
#define ASTEROIDS_MAIN_FUNCS_H

#include <vector>
#include <set>

#include "../Objects/Ship.h"
#include "../Objects/Asteroid.h"
#include "../Objects/Bullet.h"

using std::vector;

/**
 * Creation of visible asteroid's copies func
 *
 * @param obj asteroid or ship object
 */
std::set<vector<float>> get_object_copies(BaseObject & obj);

/**
 * Function that checks collision between objects
 *
 * @param a Asteroid
 * @param s Ship
 */
bool check_collision(Asteroid& a, Ship& s);

/**
 * Spit asteroid after destruction
 *
 * @param aas asteroid array
 * @param a origin asteroid
 */
void split_asteroid(vector<Asteroid> & aas, Asteroid & a);

#endif //ASTEROIDS_MAIN_FUNCS_H
