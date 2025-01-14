#pragma once

#include <pybind11/pybind11.h>
#include "float32.hh"

namespace py = pybind11;

namespace auto_th10::obj {

struct ThObject {};

}  // namespace auto_th10::obj

namespace auto_th10::details {

template<typename Child>
class ThObject_ : public obj::ThObject {
protected:
    float32_type x_{}, y_{};

public:
    inline ThObject_() noexcept = delete;

    inline ThObject_(float32_type x, float32_type y) noexcept
        : x_(x), y_(y) {
    }

    inline float32_type get_x() const noexcept {
        return this->x_;
    }

    inline float32_type get_y() const noexcept {
        return this->y_;
    }

    inline float32_type get_width() const noexcept {
        return (static_cast<Child const*>(this))->width;
    }

    inline float32_type get_height() const noexcept {
        return (static_cast<Child const*>(this))->height;
    }
};

}  // namespace auto_th10::details

namespace auto_th10::obj {

class Player : public details::ThObject_<Player> {
    friend class details::ThObject_<Player>;
    static constexpr float32_type width{4}, height{4};

public:
    inline Player() noexcept = delete;
    ~Player() = default;

    inline Player(float32_type x, float32_type y) noexcept
        : ThObject_(x, y) {
    }

    inline py::str __repr__() const noexcept {
        return py::str("Player(x={}, y={})").format(this->x_, this->y_);
    }
};

class Enemy : public details::ThObject_<Enemy> {
    friend class details::ThObject_<Enemy>;
    float32_type width, height;

public:
    inline Enemy() noexcept = delete;
    ~Enemy() = default;

    inline Enemy(float32_type x, float32_type y, float32_type width, float32_type height) noexcept
        : ThObject_(x, y), width(width), height(height) {
    }

    inline py::str __repr__() const noexcept {
        return py::str("Enemy(x={}, y={}, width={}, height={})").format(this->x_, this->y_, this->width, this->height);
    }
};

class EnemyBullet : public details::ThObject_<EnemyBullet> {
    friend class details::ThObject_<EnemyBullet>;
    // dx, dy : bullet's derection is `dy / dx`
    // TODO : I just gain the derection, can I gain the step bullet will move
    float32_type width, height, dx, dy;

public:
    inline EnemyBullet() noexcept = delete;
    ~EnemyBullet() = default;

    inline EnemyBullet(float32_type x, float32_type y, float32_type width, float32_type height, float32_type dx,
                       float32_type dy) noexcept
        : ThObject_(x, y), width(width), height(height), dx(dx), dy(dy) {
    }

    inline float32_type get_direction() const noexcept {
        return dy / dx;
    }

    inline py::str __repr__() const noexcept {
        return py::str("EnemyBullet(x={}, y={}, width={}, height={}, dx={}, dy={})")
            .format(this->x_, this->y_, this->width, this->height, this->dx, this->dy);
    }
};

class EnemyLaser : public details::ThObject_<EnemyLaser> {
    friend class details::ThObject_<EnemyLaser>;
    float32_type width, height, radian;

public:
    inline EnemyLaser() noexcept = delete;
    ~EnemyLaser() = default;

    inline EnemyLaser(float32_type x, float32_type y, float32_type width, float32_type height,
                      float32_type radian) noexcept
        : ThObject_(x, y), width(width), height(height), radian(radian) {
    }

    inline py::str __repr__() const noexcept {
        return py::str("EnemyLaser(x={}, y={}, width={}, height={}, radian={})")
            .format(this->x_, this->y_, this->width, this->height, this->radian);
    }

    inline float32_type get_radian() const noexcept {
        return this->radian;
    }
};

class Resource : public details::ThObject_<Resource> {
    friend class details::ThObject_<Resource>;
    static constexpr float32_type width{6}, height{6};

public:
    inline Resource() noexcept = delete;
    ~Resource() = default;

    inline Resource(float32_type x, float32_type y) noexcept
        : ThObject_(x, y) {
    }

    inline py::str __repr__() const noexcept {
        return py::str("Resource(x={}, y={})").format(this->x_, this->y_);
    }
};

}  // namespace auto_th10::obj
