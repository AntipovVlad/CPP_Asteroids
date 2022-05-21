#include "BaseObject.h"
#include <cmath>

BaseObject::BaseObject(float W, float H): w((float)W), h((float)H) {}

void BaseObject::move() {}

void BaseObject::rotate() {
    angle += dangle;
}

vector<vector<float>> BaseObject::gen_virtual_dots(float d_x, float d_y) {
    vector<vector<float>> new_dots;

    for (auto &d : dots)
        new_dots.push_back({
           d_x + d[0] * std::cos(angle) - d[1] * std::sin(angle),
           d_y + d[0] * std::sin(angle) + d[1] * std::cos(angle)
       });

    return new_dots;
}

vector<vector<float>> BaseObject::gen_true_dots(float d_x, float d_y) {
    vector<vector<float>> new_dots;
    float ww, hh;
    for (auto &d : dots) {
        ww = d_x + d[0] * std::cos(angle) - d[1] * std::sin(angle);
        hh = d_y + d[0] * std::sin(angle) + d[1] * std::cos(angle);

        if (ww < 0) ww += w;
        if (hh < 0) hh += h;
        if (ww > w) ww -= w;
        if (hh > h) hh -= h;

        new_dots.push_back({ww, hh});
    }

    return new_dots;
}

bool BaseObject::dot_inside(vector<float> center, float x0, float y0) {
    float dt, angle_sum = 0.f, a, b, c, d;

    vector<vector<float>> c_dots = gen_virtual_dots(center[0], center[1]);
    for (int i = 0; i < dots.size(); i++) {
        a = c_dots[i][0] - x0;
        b = c_dots[i][1] - y0;
        c = c_dots[(i + 1) % dots.size()][0] - x0;
        d = c_dots[(i + 1) % dots.size()][1] - y0;

        dt = a * d - b * c;
        if (dt > 0) angle_sum -= std::acos((a * c + b * d) / std::sqrt((a * a + b * b) * (c * c + d * d)));
        else angle_sum += std::acos((a * c + b * d) / std::sqrt((a * a + b * b) * (c * c + d * d)));
    }

    return std::fabs(angle_sum) >= 0.001;
}

float BaseObject::get_x() const {
    return x;
}

float BaseObject::get_y() const {
    return y;
}

int BaseObject::get_size() const {
    return size;
}

float BaseObject::get_h() const {
    return h;
}

float BaseObject::get_w() const {
    return w;
}
