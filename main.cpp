#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

/*#include "Objects/Ship.h"
#include "Objects/Asteroid.h"
#include "Objects/Bullet.h"*/

#include "View/main_funcs.h"
#include "View/main_screen_out.h"

#include <SFML/Graphics.hpp>

using std::vector;

const int WIDTH = 1200; //!< Screen width
const int HEIGHT = 800; //!< Screen height

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
            draw_object(window, (BaseObject &)a);
        }

        for (auto &b : bullets) {
            b.move(dt);
            draw_bullet(window, b);
        }

        if (!ship.is_destroyed()) {
            draw_object(window, (BaseObject &)ship);

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
