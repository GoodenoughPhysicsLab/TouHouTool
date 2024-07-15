#include <pybind11/pybind11.h>
#include "default_print.hh"

PYBIND11_MODULE(default_print, m) {
    m.def("default_print", thtool::default_print);
}