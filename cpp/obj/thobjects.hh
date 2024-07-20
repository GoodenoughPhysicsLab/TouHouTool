#pragma once

#include "../../_float32.hh"

namespace thtool::obj {

struct ThObject {
    ThObject() = default;
};

} // namespace thtool::obj

namespace thtool::details {

template<typename Child>
class ThObject_ : public obj::ThObject {
protected:
    f32::float32_type x_{}, y_{};
public:
    ThObject_() = delete;
    ThObject_(double x, double y)
        : x_(x), y_(y) {}

    double get_width() { return (static_cast<Child*>(this))->width; }
    double get_height() { return (static_cast<Child*>(this))->height; }
};

} // namespace thtool::details

namespace thtool::obj {

class Player : public details::ThObject_<Player> {
    friend class details::ThObject_<Player>;
    static constexpr double width{2}, height{2};
public:
    Player() = delete;
    Player(double x, double y) : ThObject_(x, y) {}
};

class Enemy : public details::ThObject_<Enemy> {
    //
};

class EnemyBullet : public details::ThObject_<EnemyBullet> {
    //
};

class EnemyLaser : public details::ThObject_<EnemyLaser> {
    //
};

// Resources : like Power, ...
class Resource : public details::ThObject_<Resource> {
    //
};

} // namespace thtool::obj