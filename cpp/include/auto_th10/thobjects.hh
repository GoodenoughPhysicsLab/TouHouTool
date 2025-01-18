#pragma once

#include "float32.hh"

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
        : x_{x}, y_{y} {
    }

    inline float32_type get_x(this ThObject_<Child> const& self) noexcept {
        return self.x_;
    }

    inline float32_type get_y(this ThObject_<Child> const& self) noexcept {
        return self.y_;
    }

    inline float32_type get_width(this auto const& self) noexcept {
        return self.width;
    }

    inline float32_type get_height(this auto const& self) noexcept {
        return self.height;
    }
};

}  // namespace auto_th10::details

namespace auto_th10::obj {

class Player : public details::ThObject_<Player> {
    friend class details::ThObject_<Player>;
    static constexpr float32_type width{4}, height{4};

public:
    inline Player() noexcept = delete;

    inline Player(float32_type x, float32_type y) noexcept
        : ThObject_{x, y} {
    }
};

class Enemy : public details::ThObject_<Enemy> {
    friend class details::ThObject_<Enemy>;
    float32_type width, height;

public:
    inline Enemy() noexcept = delete;

    inline Enemy(float32_type x, float32_type y, float32_type width, float32_type height) noexcept
        : ThObject_{x, y}, width{width}, height{height} {
    }
};

class EnemyBullet : public details::ThObject_<EnemyBullet> {
    friend class details::ThObject_<EnemyBullet>;
    // dx, dy : bullet's derection is `dy / dx`
    // TODO : I just gain the derection, can I gain the step bullet will move
    float32_type width, height, dx, dy;

public:
    inline EnemyBullet() noexcept = delete;

    inline EnemyBullet(float32_type x, float32_type y, float32_type width, float32_type height, float32_type dx,
                       float32_type dy) noexcept
        : ThObject_{x, y}, width{width}, height{height}, dx{dx}, dy{dy} {
    }

    inline float32_type get_direction(this EnemyBullet const& self) noexcept {
        return self.dy / self.dx;
    }
};

class EnemyLaser : public details::ThObject_<EnemyLaser> {
    friend class details::ThObject_<EnemyLaser>;
    float32_type width, height, radian;

public:
    inline EnemyLaser() noexcept = delete;

    inline EnemyLaser(float32_type x, float32_type y, float32_type width, float32_type height,
                      float32_type radian) noexcept
        : ThObject_{x, y}, width{width}, height{height}, radian{radian} {
    }

    inline float32_type get_radian(this EnemyLaser const& self) noexcept {
        return self.radian;
    }
};

class Resource : public details::ThObject_<Resource> {
    friend class details::ThObject_<Resource>;
    static constexpr float32_type width{6}, height{6};

public:
    inline Resource() noexcept = delete;

    inline Resource(float32_type x, float32_type y) noexcept
        : ThObject_(x, y) {
    }
};

}  // namespace auto_th10::obj
