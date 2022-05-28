cmake_minimum_required(VERSION 3.22)

enable_testing()

add_executable(project_test ../Objects/Asteroid.cpp ../Objects/BaseObject.cpp ../Objects/Bullet.cpp ../Objects/Ship.cpp ../View/main_funcs.cpp test.cpp)
target_link_libraries(project_test PUBLIC doctest default)
add_test(NAME project_test COMMAND project_test --force-colors -d -ldefault)
