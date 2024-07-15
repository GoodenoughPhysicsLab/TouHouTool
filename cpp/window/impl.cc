#include "bind.hh"
// #include "window.hh"
#include "keyboard.hh"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(window, m) {
    py::register_exception<thtool::bind::BindError>(m, "BindError");

    m.def("send_behavior", thtool::keyboard::send_behavior);
    m.def("print_all_windows", thtool::bind::print_all_windows, py::arg("only_guess")=false);
    m.def("bind_foreground", thtool::bind::bind_foreground);
    m.def("bind_guess", thtool::bind::bind_guess);
    m.def("bind_title", thtool::bind::bind_title);

    // m.def("get_scene", thtool::window::get_scene);
}