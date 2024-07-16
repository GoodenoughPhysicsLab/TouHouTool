#include "kb_control.hh"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(kb_control, m) {
    m.doc() = "send keyboard event to TouHou window";
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