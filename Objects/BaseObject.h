#ifndef ASTEROIDS_BASEOBJECT_H
#define ASTEROIDS_BASEOBJECT_H
#include <vector>
using std::vector;

class BaseObject {
protected:
    float h;
    float w;
    float x{};
    float y{};
    float angle = 0.f;
    float speed{};
    float dangle{};
    int size{};
    vector<vector<float>> dots;
public:
    BaseObject(float W, float H);

    virtual void move();
    virtual void rotate();

    vector<vector<float>> gen_virtual_dots(float d_x, float d_y);
    vector<vector<float>> gen_true_dots(float d_x, float d_y);

    bool dot_inside(vector<float> center, float x0, float y0);

    float get_x() const;
    float get_y() const;
    int get_size() const;
};


#endif //ASTEROIDS_BASEOBJECT_H
