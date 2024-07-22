#include "bind.hh"
#include "window.hh"
#include "readmem/th10_fsl.hh"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(window, m) {
    py::register_exception<thtool::bind::BindError>(m, "BindError");
    py::register_exception<thtool::readmem::GameNotStartError>(m, "GameNotStartError");

    m.def("print_all_windows", thtool::bind::print_all_windows, py::arg("only_guess")=false);
    m.def("bind_foreground", thtool::bind::bind_foreground);
    m.def("bind_guess", thtool::bind::bind_guess);
    m.def("bind_title", thtool::bind::bind_title);

    m.def("init_Gdiplus", thtool::window::init_Gdiplus);
    m.def("free_Gdiplus", thtool::window::free_Gdiplus);
    m.def("save_scene_img", thtool::window::save_scene_img);
    m.def("is_foreground", thtool::window::is_foreground);

    m.def("fsl_get_player", thtool::readmem::fsl_get_player);
    m.def("fsl_get_enemies", thtool::readmem::fsl_get_enemies);
    m.def("fsl_get_enemy_bullets", thtool::readmem::fsl_get_enemy_bullets);
    m.def("fsl_get_resources", thtool::readmem::fsl_get_resources);
}
