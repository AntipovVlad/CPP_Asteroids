#include <iostream>
#include <vector>
#include "Objects/Ship.h"
#include "Objects/Asteroid.h"
#include "Objects/Bullet.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <chrono>
#include <cmath>

using std::vector;

const int WIDTH = 1200; //!< Screen width
const int HEIGHT = 800; //!< Screen height

/**
 * Creation of visible object's copies func
 *
 * @param obj Game object (asteroid or ship)
 */
template<typename T>
std::set<vector<float>> get_object_copies(T obj) {
    float x = obj.get_x();
    float y = obj.get_y();

    std::set<vector<float>> delta {{x, y}};

    for (auto &c : obj.gen_virtual_dots(x, y)) {
        if (c[1] < 0) delta.insert({x, (float)HEIGHT + y});
        if (c[0] < 0) delta.insert({(float)WIDTH + x, y});
        if (c[1] > (float)HEIGHT) delta.insert({x, -(float)HEIGHT + y});
        if (c[0] > (float)WIDTH) delta.insert({-(float)WIDTH + x, y});
    }

    return delta;
}

/**
 * Draw objects
 *
 * @param win game window
 * @param obj Game object (asteroid or ship)
 */
template<typename T>
void draw_object(sf::RenderWindow &win, T& obj) {
    float x = obj.get_x();
    float y = obj.get_y();
    int size = obj.get_size();
    int i = 0, l = 0;

    std::set<vector<float>> delta = get_object_copies(obj);

    vector<sf::VertexArray> lines_arr(delta.size());
    for (int j = 0; j < delta.size(); j++) {
        sf::VertexArray lines(sf::LinesStrip, size);
        lines_arr[j] = lines;
    }

    for (auto &d : delta) {
        i = 0;

        for (auto &dot : obj.gen_virtual_dots(d[0], d[1]))
            lines_arr[l][i++].position = sf::Vector2f(dot[0], dot[1]);

        lines_arr[l][i].position = lines_arr[l][0].position;

        win.draw(lines_arr[l]);

        l++;
    }
}

/**
 * Draw bullets
 *
 * @param win game window
 * @param obj Game object (asteroid or ship)
 */
void draw_bullet(sf::RenderWindow &win, Bullet& obj) {
    sf::CircleShape b;
    b.setRadius(1);
    b.setPosition(obj.get_x(), obj.get_y());
    b.setFillColor(sf::Color::Red);
    b.setOutlineColor(sf::Color::Red);
    win.draw(b);
}

/**
 * Function that checks collision between objects
 *
 * @param obj1 Game object (asteroid, ship or bullet)
 * @param obj2 Game object (asteroid, ship or bullet)
 */
template<typename T1, typename T2>
bool check_collision(T1& obj1, T2& obj2) {
    for (auto & dc : get_object_copies(obj1))
        for (auto & d : obj2.gen_true_dots(obj2.get_x(), obj2.get_y()))
            if (obj1.dot_inside(dc, d[0], d[1]))
                return true;

    for (auto & dc : get_object_copies(obj2))
        for (auto & d : obj1.gen_true_dots(obj1.get_x(), obj1.get_y()))
            if (obj2.dot_inside(dc, d[0], d[1]))
                return true;


    return false;
}

/**
 * Spit asteroid after destruction
 *
 * @param aas asteroid array
 * @param a origin asteroid
 */
void split_asteroid(vector<Asteroid> & aas, Asteroid & a) {
    a.make_invalid();

    if (a.get_hp_size() == 1)
        return;

    aas.emplace_back(Asteroid{(float)WIDTH, (float)HEIGHT, a.get_x(), a.get_y(), a.get_hp_size() - 1});
    aas.emplace_back(Asteroid{(float)WIDTH, (float)HEIGHT, a.get_x(), a.get_y(), a.get_hp_size() - 1});
}

/**
 * Main loop function
 */
int main() {
    float dt;
    int score = 100;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Asteroid", sf::Style::Default, settings);
    sf::Font font;
    sf::Text info_score;
    sf::Text info_hp;

    Ship ship{(float)WIDTH, (float)HEIGHT};
    vector<Asteroid> asteroids;
    vector<Asteroid> new_asteroids;
    vector<Bullet> bullets;

    sf::Clock sf_clock;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point safe_time_start = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point respawn_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point bullet_time = std::chrono::steady_clock::now();

    font.loadFromFile("../Fonts/arial.ttf");

    info_score.setFont(font);
    info_score.setString("Score: " + std::to_string(score) + "\t\tHp: " + std::to_string(ship.get_hp()));
    info_score.setCharacterSize(16);
    info_score.setPosition(0.f, 0.f);

    while (window.isOpen()) {
        window.clear();
        dt = sf_clock.restart().asSeconds();

        sf::Event event{};
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if (asteroids.size() < 100 && std::chrono::steady_clock::now() >= start + std::chrono::seconds(5)) {
            start = std::chrono::steady_clock::now();
            Asteroid a{(float)WIDTH, (float)HEIGHT};

            if (std::pow((ship.get_x() - a.get_x()), 2) + std::pow((ship.get_y() - a.get_y()), 2) > 40000.f)
                asteroids.emplace_back(Asteroid{(float)WIDTH, (float)HEIGHT, a.get_x(), a.get_y(), a.get_hp_size()});
        }

        if (ship.is_destroyed() && std::chrono::steady_clock::now() > respawn_time + std::chrono::seconds(2)) {
            ship.respawn_ship();
            safe_time_start = std::chrono::steady_clock::now();
            ship.change_safe_mode();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ship.rotate(dt,true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ship.rotate(dt,false);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ship.move(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))  {
            if (score > 0 && !ship.is_destroyed())
                if (std::chrono::steady_clock::now() > bullet_time + std::chrono::milliseconds(200)) {
                    bullets.emplace_back(Bullet{(float)WIDTH, (float)HEIGHT, ship.gen_true_dots(ship.get_x(), ship.get_y())[0], ship.get_angle()});
                    bullet_time = std::chrono::steady_clock::now();
                    score -= 1;
                }
        }

        // Check all collisions
        for (auto &a : asteroids)
            if (!ship.is_destroyed() && !ship.is_safe() && check_collision(a, ship)) {
                ship.destroy_ship();
                if (ship.is_alive())
                    respawn_time = std::chrono::steady_clock::now();
                else
                    break;
            }

        for (auto &a : asteroids)
            for (auto &dc : get_object_copies(a))
                for (auto &b : bullets)
                    if (a.dot_inside(dc, b.get_x(), b.get_y())) {
                        a.gain_damage();

                        if (a.get_hp() == 0)
                            split_asteroid(new_asteroids, a);

                        b.make_invalid();

                        score += 16;
                    }
        // =============================================================================================================


        // Change of asteroid number
        asteroids.erase(std::remove_if(asteroids.begin(),
                                       asteroids.end(),
                                       [](auto & a){return !a.is_valid();}), asteroids.end());
        bullets.erase(std::remove_if(bullets.begin(),
                                     bullets.end(),
                                     [](auto & b){return !b.is_valid();}), bullets.end());

        asteroids.insert(asteroids.end(), new_asteroids.begin(), new_asteroids.end());
        new_asteroids.clear();
        // =============================================================================================================

        // Drawing objects and info
        for (auto &a: asteroids) {
            a.move(dt);
            a.rotate(dt);
            draw_object(window, a);
        }

        for (auto &b : bullets) {
            b.move(dt);
            draw_bullet(window, b);
        }

        if (!ship.is_destroyed()) {
            draw_object(window, ship);

            if (ship.is_safe() && std::chrono::steady_clock::now() > safe_time_start + std::chrono::seconds(2))
                ship.change_safe_mode();
        }

        info_score.setString("Score: " + std::to_string(score) + "\t\tHp: " + std::to_string(ship.get_hp()));
        window.draw(info_score);
        // =============================================================================================================

        window.display();

        if (!ship.is_alive() || score == 0)
            break;
    }

    std::cout << "Game over";

    return 0;
}
