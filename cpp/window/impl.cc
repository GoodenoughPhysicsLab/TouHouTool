#include "bind.hh"
#include "window.hh"
#include "readmem/th10_fsl.hh"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(window, m) {
    py::register_exception<thtool::bind::BindError>(m, "BindError");
    py::register_exception<thtool::readmem::GameNotStartError>(m, "GameNotStartError");

    py::enum_<thtool::bind::ThGame>(m, "ThGame")
        .value("yym", thtool::bind::ThGame::yym)
        .value("yyc", thtool::bind::ThGame::yyc)
        .value("fsl", thtool::bind::ThGame::fsl)
        .value("dld", thtool::bind::ThGame::dld)
        .value("xlc", thtool::bind::ThGame::xlc)
        .value("slm", thtool::bind::ThGame::slm)
        .value("hzc", thtool::bind::ThGame::hzc)
        .value("gzz", thtool::bind::ThGame::gzz)
        .value("tkz", thtool::bind::ThGame::tkz)
        .value("gxs", thtool::bind::ThGame::gxs)
        .value("hld", thtool::bind::ThGame::hld)
        .export_values();

    m.def("get_th_game", thtool::bind::get_th_game);
    m.def("print_all_windows", thtool::bind::print_all_windows, py::arg("only_guess")=false);
    m.def("bind_foreground", thtool::bind::bind_foreground);
    m.def("bind_auto", thtool::bind::bind_auto);
    m.def("bind_title", thtool::bind::bind_title);

    m.def("init_Gdiplus", thtool::window::init_Gdiplus);
    m.def("free_Gdiplus", thtool::window::free_Gdiplus);
    m.def("get_size", thtool::window::get_size);
    m.def("save_scene_img", thtool::window::save_scene_img);
    m.def("is_foreground", thtool::window::is_foreground);

    m.def("fsl_get_player", thtool::readmem::fsl_get_player);
    m.def("fsl_get_enemies", thtool::readmem::fsl_get_enemies);
    m.def("fsl_get_enemy_bullets", thtool::readmem::fsl_get_enemy_bullets);
    m.def("fsl_get_enemy_lasers", thtool::readmem::fsl_get_enemy_lasers);
    m.def("fsl_get_resources", thtool::readmem::fsl_get_resources);
}
