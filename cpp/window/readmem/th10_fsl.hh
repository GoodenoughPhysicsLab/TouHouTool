#pragma once

#include <Windows.h>
#include <basetsd.h>
#include <memoryapi.h>
#include <pybind11/pytypes.h>
#include <windef.h>
#include "_pid.hh"
#include "errors.hh"
#include "pybind11/cast.h"
#include "../../_float32.hh"

namespace thtool::readmem {

inline py::tuple fsl_get_player() {
    f32::float32_type x, y;
    uintmax_t obj_base;
    SIZE_T nbr;
    ReadProcessMemory(details::get_process_handle(),
                      LPCVOID(0x00477834),
                      &obj_base,
                      SIZE_T(4),
                      &nbr);
    if (obj_base == 0) {
        throw GameNotStartError( "checking game NOT start(don't means touhou window not open)");
    }
    ReadProcessMemory(details::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C0),
                      &x,
                      4,
                      &nbr);
    ReadProcessMemory(details::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C4),
                      &y,
                      4,
                      &nbr);

    return py::make_tuple(x, y);
}

}