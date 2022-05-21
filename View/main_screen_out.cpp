#include "main_screen_out.h"
#include "main_funcs.h"

void draw_object(sf::RenderWindow &win, BaseObject& obj) {
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

void draw_bullet(sf::RenderWindow &win, Bullet& obj) {
    sf::CircleShape b;
    b.setRadius(1);
    b.setPosition(obj.get_x(), obj.get_y());
    b.setFillColor(sf::Color::Red);
    b.setOutlineColor(sf::Color::Red);
    win.draw(b);
}

void draw_object(sf::RenderWindow &win, Asteroid& obj);
void draw_object(sf::RenderWindow &win, Ship& obj);
