#include "main_funcs.h"

std::set<vector<float>> get_object_copies(BaseObject & obj) {
    float x = obj.get_x();
    float y = obj.get_y();
    float h = obj.get_h();
    float w = obj.get_w();

    std::set<vector<float>> delta {{x, y}};

    for (auto &c : obj.gen_virtual_dots(x, y)) {
        if (c[1] < 0) delta.insert({x, h + y});
        if (c[0] < 0) delta.insert({w + x, y});
        if (c[1] > h) delta.insert({x, -h + y});
        if (c[0] > w) delta.insert({-w + x, y});
    }

    return delta;
}

bool check_collision(Asteroid& a, Ship& s) {
    for (auto & dc : get_object_copies(a))
        for (auto & d : s.gen_true_dots(s.get_x(), s.get_y()))
            if (a.dot_inside(dc, d[0], d[1]))
                return true;

    for (auto & dc : get_object_copies(s))
        for (auto & d : s.gen_true_dots(a.get_x(), a.get_y()))
            if (s.dot_inside(dc, d[0], d[1]))
                return true;


    return false;
}

void split_asteroid(vector<Asteroid> & aas, Asteroid & a) {
    a.make_invalid();

    if (a.get_hp_size() == 1)
        return;

    aas.emplace_back(Asteroid{a.get_w(), a.get_h(), a.get_x(), a.get_y(), a.get_hp_size() - 1});
    aas.emplace_back(Asteroid{a.get_w(), a.get_h(), a.get_x(), a.get_y(), a.get_hp_size() - 1});
}
