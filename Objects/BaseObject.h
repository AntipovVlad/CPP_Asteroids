#pragma once

#include <vector>
using std::vector;

/**
 * @brief Base class for game objects
 */
class BaseObject {
protected:
    float h; //!< window height
    float w; //!< window width
    float x{}; //!< x coordinate
    float y{}; //!< y coordinate
    float angle = 0.f; //!< rotation angle
    float speed{}; //<! speed of object
    float dangle{}; //<! frame rotation
    int size{}; //<! object size param
    vector<vector<float>> dots; //<! array of dots
public:
    /**
     * @brief Default constructor
     * @param W width of screen
     * @param H height of screen
     */
    BaseObject(float W, float H);

    BaseObject(BaseObject && bs) noexcept : h(bs.h), w(bs.w), x(bs.x), y(bs.y), angle(bs.angle), speed(bs.speed), dangle(bs.dangle), size(bs.size), dots(bs.dots) {}
    BaseObject(BaseObject & bs) : h(bs.h), w(bs.w), x(bs.x), y(bs.y), angle(bs.angle), speed(bs.speed), dangle(bs.dangle), size(bs.size), dots(bs.dots) {}
    BaseObject& operator=(BaseObject & bs) = default;
    BaseObject& operator=(BaseObject && bs) = default;

    /**
     * @brief Asteroid move func
     */
    virtual void move();

    /**
     * @brief Asteroid rotation func
     */
    virtual void rotate();

    /**
     * @brief Asteroid dot generation with coordinates for display func
     * @param d_x x center coordinate
     * @param d_y y center coordinate
     */
    vector<vector<float>> gen_virtual_dots(float d_x, float d_y);

    /**
     * @brief Asteroid dot generation with real coordinates func
     * @param d_x x center coordinate
     * @param d_y y center coordinate
     */
    vector<vector<float>> gen_true_dots(float d_x, float d_y);

    /**
     * @brief Asteroid check whether dot inside object or not
     * @param center coordinate of asteroid's center clone
     * @param x0 x dot coordinate
     * @param y0 y dot coordinate
     */
    bool dot_inside(vector<float> center, float x0, float y0);

    /**
     * @brief Returns object's x coordinate
     */
    float get_x() const;

    /**
     * @brief Returns object's y coordinate
     */
    float get_y() const;

    /**
     * @brief Returns object's size
     */
    int get_size() const;

    /**
     * @brief Returns screen's height
     */
    float get_h() const;

    /**
     * @brief Returns screen's width
     */
    float get_w() const;
};
