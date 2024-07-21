#pragma once

#include <Windows.h>
#include <basetsd.h>
#include <cstdint>
#include <memoryapi.h>
#include <tuple>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>
#include <vector>
#include <windef.h>
#include "_pid.hh"
#include "errors.hh"
#include "../../_float32.hh"

namespace thtool::readmem {

#ifdef _MSC_VER
#pragma warning(disable: 4312)
#endif

inline auto fsl_get_player() {
    f32::float32_type x, y;
    int32_t obj_base;
    SIZE_T nbr;
    ReadProcessMemory(details::get_process_handle(),
                      LPCVOID(0x00477834),
                      &obj_base,
                      SIZE_T(4),
                      &nbr);
    if (obj_base == 0) {
        throw GameNotStartError();
    }
    ReadProcessMemory(details::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C0),
                      &x,
                      SIZE_T(4),
                      &nbr);
    ReadProcessMemory(details::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C4),
                      &y,
                      SIZE_T(4),
                      &nbr);

    return ::std::make_tuple(x, y);
}

inline auto fsl_get_enemy() {
    //
}

inline auto fsl_get_enemy_bullet() {
    //
}

inline auto fsl_get_resources() {
    SIZE_T nbr;
	int32_t base;
	ReadProcessMemory(details::get_process_handle(),
                     LPCVOID(0x00477818),
                     &base,
                     SIZE_T(4),
                     &nbr);
	if (base == 0) {
		throw GameNotStartError();
	}
	int32_t esi = base + 0x14;
	int32_t ebp = esi + 0x3B0;
    ::std::vector<::std::tuple<f32::float32_type, f32::float32_type>> res{};

	for (int i = 0; i < 2000; i++)
	{
		int32_t eax;
		ReadProcessMemory(details::get_process_handle(),
                          reinterpret_cast<LPCVOID>(ebp + 0x2C),
                          &eax,
                          SIZE_T(4),
                          &nbr);
		if (eax != 0) {
			f32::float32_type x, y;
			ReadProcessMemory(details::get_process_handle(),
                              reinterpret_cast<LPCVOID>(ebp - 0x4),
                              &x,
                              SIZE_T(4),
                              &nbr);
			ReadProcessMemory(details::get_process_handle(),
                              reinterpret_cast<LPCVOID>(ebp),
                              &y,
                              SIZE_T(4),
                              &nbr);
			res.emplace_back(x, y);
		}
		ebp += 0x3F0;
	}
    return res;
}

#ifdef _MSC_VER
#pragma warning(default: 4312)
#endif

} // namespace thtool::readmem
