#include "bind.hh"
#include "keyboard.hh"
#include "../pybind11/pybind11.h"

PYBIND11_MODULE(window, m) {
    m.def("send_behavior", thtool::keyboard::send_behavior);
    m.def("print_all_windows", thtool::bind::print_all_windows);
    m.def("set_hwnd_foreground", thtool::bind::set_hwnd_foreground);
}