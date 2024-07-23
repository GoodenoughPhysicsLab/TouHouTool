#pragma once

#include <pybind11/pybind11.h>
#include "../../_float32.hh"
#include "pybind11/pytypes.h"

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

    f32::float32_type get_x() { return this->x_; }
    f32::float32_type get_y() { return this->y_; }

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
    friend class details::ThObject_<Enemy>;
    f32::float32_type width, height;
public:
    Enemy() = delete;
    ~Enemy() = default;
    Enemy(f32::float32_type x, f32::float32_type y, f32::float32_type width, f32::float32_type height)
        : ThObject_(x, y), width(width), height(height) {}

    py::str __repr__() const {
        return py::str("Enemy(x={}, y={}, width={}, height={})")
                .format(this->x_, this->y_, this->width, this->height);
    }
};

class EnemyBullet : public details::ThObject_<EnemyBullet> {
    friend class details::ThObject_<EnemyBullet>;
    // dx, dy : bullet's derection is `dy / dx`
    // TODO : I just gain the derection, can I gain the step bullet will move
    f32::float32_type width, height, dx, dy;
public:
    EnemyBullet() = delete;
    ~EnemyBullet() = default;
    EnemyBullet(f32::float32_type x,
                f32::float32_type y,
                f32::float32_type width,
                f32::float32_type height,
                f32::float32_type dx,
                f32::float32_type dy)
        : ThObject_(x, y), width(width), height(height), dx(dx), dy(dy) {}

    f32::float32_type get_direction() const noexcept {
        return dy / dx;
    }

    py::str __repr__() const {
        return py::str("EnemyBullet(x={}, y={}, width={}, height={}, dx={}, dy={})")
               .format(this->x_, this->y_, this->width, this->height, this->dx, this->dy);
    }
};

class EnemyLaser : public details::ThObject_<EnemyLaser> {
    friend class details::ThObject_<EnemyLaser>;
    f32::float32_type width, height, radian;
public:
    EnemyLaser() = delete;
    ~EnemyLaser() = default;

    EnemyLaser(f32::float32_type x,
                f32::float32_type y,
                f32::float32_type width,
                f32::float32_type height,
                f32::float32_type radian)
        : ThObject_(x, y), width(width), height(height), radian(radian) {}

    py::str __repr__() const {
        return py::str("EnemyLaser(x={}, y={}, width={}, height={}, radian={})")
               .format(this->x_, this->y_, this->width, this->height, this->radian);
    }

    f32::float32_type get_radian() const noexcept {
        return this->radian;
    }
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
