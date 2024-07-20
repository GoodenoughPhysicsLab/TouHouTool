#include <pybind11/pybind11.h>
#include "thobjects.hh"

namespace py = pybind11;

PYBIND11_MODULE(obj, m) {
    py::class_<thtool::obj::ThObject>(m, "ThObject")
        .def(py::init<>());

    py::class_<thtool::obj::Player>(m, "Player")
        .def(py::init<double, double>())
        .def("get_width", &thtool::obj::Player::get_width)
        .def("get_height", &thtool::obj::Player::get_height);
}