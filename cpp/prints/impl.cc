#include <pybind11/pybind11.h>
#include "prints.hh"

PYBIND11_MODULE(prints, m) {
    m.def("enable_win32_ansi", thtool::prints::enable_win32_ansi);
    m.def("set_win32_console_io_cp_to_utf8",
          thtool::prints::set_win32_console_io_cp_to_utf8);
    m.def("cancle_set_win32_console_io_cp_to_utf8",
          thtool::prints::cancle_set_win32_console_io_cp_to_utf8);
}
