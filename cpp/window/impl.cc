#include "bind.hh"
#include "window.hh"
#include "kb_control.hh"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(window, m) {
    py::register_exception<thtool::bind::BindError>(m, "BindError");

    m.def("print_all_windows", thtool::bind::print_all_windows, py::arg("only_guess")=false);
    m.def("bind_foreground", thtool::bind::bind_foreground);
    m.def("bind_guess", thtool::bind::bind_guess);
    m.def("bind_title", thtool::bind::bind_title);

    m.def("init_Gdiplus", thtool::window::init_Gdiplus);
    m.def("free_Gdiplus", thtool::window::free_Gdiplus);
    m.def("save_scene_img", thtool::window::save_scene_img);

    py::enum_<thtool::kb_control::Behavior>(m, "Behavior")
        .value("left", thtool::kb_control::Behavior::left)
        .value("up", thtool::kb_control::Behavior::up)
        .value("right", thtool::kb_control::Behavior::right)
        .value("down", thtool::kb_control::Behavior::down)
        .value("bomb", thtool::kb_control::Behavior::bomb)
        .value("shoot", thtool::kb_control::Behavior::shoot)
        .value("shift", thtool::kb_control::Behavior::shift)
        .export_values();
    m.def("send", thtool::kb_control::send);
}