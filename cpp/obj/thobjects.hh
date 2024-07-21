#pragma once

#include <pybind11/pybind11.h>
#include "../../_float32.hh"

namespace py = pybind11;

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
    ThObject_(f32::float32_type x, f32::float32_type y)
        : x_(x), y_(y) {}

    f32::float32_type get_width() { return (static_cast<Child*>(this))->width; }
    f32::float32_type get_height() { return (static_cast<Child*>(this))->height; }
};

} // namespace thtool::details

namespace thtool::obj {

class Player : public details::ThObject_<Player> {
    friend class details::ThObject_<Player>;
    static constexpr f32::float32_type width{2}, height{2};
public:
    Player() = delete;
    ~Player() = default;
    Player(f32::float32_type x, f32::float32_type y) : ThObject_(x, y) {}

    py::str __repr__() const {
        return py::str("Player(x={}, y={})").format(this->x_, this->y_);
    }
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
    friend class details::ThObject_<Resource>;
    static constexpr f32::float32_type width{6}, height{6};
public:
    Resource() = delete;
    ~Resource() = default;
    Resource(f32::float32_type x, f32::float32_type y) : ThObject_(x, y) {}

    py::str __repr__() const {
        return py::str("Resource(x={}, y={})").format(this->x_, this->y_);
    }
};

} // namespace thtool::obj
