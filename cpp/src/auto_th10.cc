#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <auto_th10/thobjects.hh>
#include <auto_th10/readmem.hh>

namespace py = pybind11;

PYBIND11_MODULE(auto_th10, m) {
    m.def("get_player", auto_th10::readmem::get_player);
    m.def("get_enemies", auto_th10::readmem::get_enemies);
    m.def("get_enemy_bullets", auto_th10::readmem::get_enemy_bullets);
    m.def("get_enemy_lasers", auto_th10::readmem::get_enemy_lasers);
    m.def("get_resources", auto_th10::readmem::get_resources);
    m.def("get_score", auto_th10::readmem::get_score);
    m.def("get_power", auto_th10::readmem::get_power);

    py::class_<auto_th10::obj::ThObject>(m, "ThObject")
        .def(py::init<>());

    py::class_<auto_th10::obj::Player>(m, "Player")
        // .def(py::init<auto_th10::float32_type, auto_th10::float32_type>())
        .def("get_x", &auto_th10::obj::Player::get_x)
        .def("get_y", &auto_th10::obj::Player::get_y)
        .def("get_width", &auto_th10::obj::Player::template get_width<auto_th10::obj::Player>)
        .def("get_height", &auto_th10::obj::Player::template get_height<auto_th10::obj::Player>);

    py::class_<auto_th10::obj::Enemy>(m, "Enemy")
        .def(py::init<auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type>())
        .def("get_x", &auto_th10::obj::Enemy::get_x)
        .def("get_y", &auto_th10::obj::Enemy::get_y)
        .def("get_width", &auto_th10::obj::Enemy::get_width<auto_th10::obj::Enemy>)
        .def("get_height", &auto_th10::obj::Enemy::get_height<auto_th10::obj::Enemy>);

    py::class_<auto_th10::obj::EnemyBullet>(m, "EnemyBullet")
        .def(py::init<auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type,
                            auto_th10::float32_type>())
        .def("get_x", &auto_th10::obj::EnemyBullet::get_x)
        .def("get_y", &auto_th10::obj::EnemyBullet::get_y)
        .def("get_width", &auto_th10::obj::EnemyBullet::get_width<auto_th10::obj::EnemyBullet>)
        .def("get_height", &auto_th10::obj::EnemyBullet::get_height<auto_th10::obj::EnemyBullet>)
        .def("get_direction", &auto_th10::obj::EnemyBullet::get_direction);

    py::class_<auto_th10::obj::EnemyLaser>(m, "EnemyLaser")
        .def(py::init<auto_th10::float32_type,
                        auto_th10::float32_type,
                        auto_th10::float32_type,
                        auto_th10::float32_type,
                        auto_th10::float32_type>())
        .def("get_x", &auto_th10::obj::EnemyLaser::get_x)
        .def("get_y", &auto_th10::obj::EnemyLaser::get_y)
        .def("get_width", &auto_th10::obj::EnemyLaser::get_width<auto_th10::obj::EnemyLaser>)
        .def("get_height", &auto_th10::obj::EnemyLaser::get_height<auto_th10::obj::EnemyLaser>)
        .def("get_radian", &auto_th10::obj::EnemyLaser::get_radian);

    py::class_<auto_th10::obj::Resource>(m, "Resource")
        .def(py::init<auto_th10::float32_type, auto_th10::float32_type>())
        .def("get_x", &auto_th10::obj::Resource::get_x)
        .def("get_y", &auto_th10::obj::Resource::get_y)
        .def("get_width", &auto_th10::obj::Resource::get_width<auto_th10::obj::Resource>)
        .def("get_height", &auto_th10::obj::Resource::get_height<auto_th10::obj::Resource>);
}
