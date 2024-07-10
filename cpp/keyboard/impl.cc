#include "keyboard.hh"
#include "../pybind11/pybind11.h"

PYBIND11_MODULE(keyboard, m) {
    m.def("send_behavior", thtool::keyboard::send_behavior);
}