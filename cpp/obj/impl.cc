#include <pybind11/pybind11.h>
#include "thobjects.hh"

namespace py = pybind11;

PYBIND11_MODULE(obj, m) {
    py::class_<thtool::obj::ThObject>(m, "ThObject")
        .def(py::init<>());

    py::class_<thtool::obj::Player>(m, "Player")
        .def(py::init<thtool::f32::float32_type, thtool::f32::float32_type>())
        .def("__repr__", &thtool::obj::Player::__repr__)
        .def("get_width", &thtool::obj::Player::get_width)
        .def("get_height", &thtool::obj::Player::get_height);

    py::class_<thtool::obj::Enemy>(m, "Enemy")
        .def(py::init<thtool::f32::float32_type,
                            thtool::f32::float32_type,
                            thtool::f32::float32_type,
                            thtool::f32::float32_type>())
        .def("__repr__", &thtool::obj::Enemy::__repr__)
        .def("get_width", &thtool::obj::Enemy::get_width)
        .def("get_height", &thtool::obj::Enemy::get_height);

    py::class_<thtool::obj::Resource>(m, "Resource")
        .def(py::init<thtool::f32::float32_type, thtool::f32::float32_type>())
        .def("__repr__", &thtool::obj::Resource::__repr__)
        .def("get_width", &thtool::obj::Resource::get_width)
        .def("get_height", &thtool::obj::Resource::get_height);
}
