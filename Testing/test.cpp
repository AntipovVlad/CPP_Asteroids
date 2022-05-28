#include "doctest.h"
#include "../View/main_funcs.h"
#include "../Objects/Asteroid.h"
#include "../Objects/BaseObject.h"
#include "../Objects/Bullet.h"
#include "../Objects/Ship.h"


class TShip : public Ship {
public:
    TShip(float W, float H) : Ship(W, H) {}
    void set_x(float en_x) {x = en_x;}
    void set_y(float en_y) {y = en_y;}
};

class TAsteroid : public Asteroid {
public:
    TAsteroid(float W, float H) : Asteroid(W, H) {}
    void set_x(float en_x) {x = en_x;}
    void set_y(float en_y) {y = en_y;}
    void set_h(float en_h) {hp = en_h;}
};


TEST_CASE("Check ship copies") {
    std::set<vector<float>> cp;
    TShip s{200, 200};

    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 1);

    s.set_x(100);
    s.set_y(0);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 2);

    s.set_x(0);
    s.set_y(100);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 2);

    s.set_x(100);
    s.set_y(200);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 2);

    s.set_x(200);
    s.set_y(100);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 2);

    s.set_x(0);
    s.set_y(0);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 3);

    s.set_x(200);
    s.set_y(200);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 3);

    s.set_x(200);
    s.set_y(0);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 3);

    s.set_x(0);
    s.set_y(200);
    cp = get_object_copies((BaseObject &)s);
    REQUIRE_EQ(cp.size(), 3);
}

TEST_CASE("Check asteroid copies") {
    std::set<vector<float>> cp;
    TAsteroid a{200, 200};

    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 1);

    a.set_x(100);
    a.set_y(0);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 2);

    a.set_x(0);
    a.set_y(100);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 2);

    a.set_x(100);
    a.set_y(200);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 2);

    a.set_x(200);
    a.set_y(100);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 2);

    a.set_x(0);
    a.set_y(0);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 3);

    a.set_x(200);
    a.set_y(200);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 3);

    a.set_x(200);
    a.set_y(0);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 3);

    a.set_x(0);
    a.set_y(200);
    cp = get_object_copies((BaseObject &)a);
    REQUIRE_EQ(cp.size(), 3);
}

TEST_CASE("Collisions") {
    TShip s{400, 400};
    TAsteroid a{400, 400};

    REQUIRE_FALSE(!check_collision(a, s));

    s.set_x(0);
    s.set_y(0);
    REQUIRE_FALSE(check_collision(a, s));
}

TEST_CASE("Splitting") {
    TAsteroid a{200, 200};

    vector<Asteroid> av;

    split_asteroid(av, a);

    REQUIRE_EQ(av.size(), 2);
}

