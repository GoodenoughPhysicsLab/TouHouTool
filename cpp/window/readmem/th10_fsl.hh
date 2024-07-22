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
    uint32_t obj_base{};
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

inline auto fsl_get_enemies() {
    SIZE_T nbr;
    uint32_t base{}, obj_base{}, obj_addr, obj_next{};

    ReadProcessMemory(details::get_process_handle(),
                      LPCVOID(0x00477704),
                      &base,
                      SIZE_T(4),
                      &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    ReadProcessMemory(details::get_process_handle(),
                      reinterpret_cast<LPCVOID>(base + 0x58),
                      &obj_base,
                      SIZE_T(4),
                      &nbr);

    ::std::vector<::std::tuple<f32::float32_type,
                                f32::float32_type,
                                f32::float32_type,
                                f32::float32_type>> res{};
    if (obj_base) {
        while (true)
        {
            ReadProcessMemory(details::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_base),
                              &obj_addr,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(details::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_base + 4),
                              &obj_next,
                              SIZE_T(4),
                              &nbr);
            obj_addr += 0x103C;
            uint32_t t;
            ReadProcessMemory(details::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_addr + 0x1444),
                              &t,
                              SIZE_T(4),
                              &nbr);
            if ((t & 0x40) == 0) {
                ReadProcessMemory(details::get_process_handle(),
                                  reinterpret_cast<LPCVOID>(obj_addr + 0x1444),
                                  &t,
                                  SIZE_T(4),
                                  &nbr);
                if ((t & 0x12) == 0) {
                    f32::float32_type x, y, w, h;
                    ReadProcessMemory(details::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0x2C),
                                      &x,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0x30),
                                      &y,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0xB8),
                                      &w,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0xBC),
                                      &h,
                                      SIZE_T(4),
                                      &nbr);
                    res.emplace_back(x, y, w, h);
                }
            }
            if (obj_next == 0) {
                break;
            }
            obj_base = obj_next;
        }
    }
    return res;
}

inline auto fsl_get_enemy_bullets() {
    uint32_t base{};
    SIZE_T nbr;
    ReadProcessMemory(details::get_process_handle(),
                    LPCVOID(0x004776F0),
                    &base,
                    SIZE_T(4),
                    &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    uint32_t ebx = base + 0x60;
    ::std::vector<::std::tuple<f32::float32_type,
                                f32::float32_type,
                                f32::float32_type,
                                f32::float32_type,
                                f32::float32_type,
                                f32::float32_type>> res{};
    for (int _{}; _ < 2000; ++_)
    {
        uint32_t edi = ebx + 0x400;
        uint32_t bp{};
        ReadProcessMemory(details::get_process_handle(),
                        reinterpret_cast<LPCVOID>(edi + 0x46),
                        &bp,
                        SIZE_T(4),
                        &nbr);
        bp &= 0x0000FFFF;
        if (bp) {
            uint32_t eax{};
            ReadProcessMemory(details::get_process_handle(),
                            reinterpret_cast<LPCVOID>(0x477810),
                            &eax,
                            SIZE_T(4),
                            &nbr);
            if (eax) {
                ReadProcessMemory(details::get_process_handle(),
                                reinterpret_cast<LPCVOID>(eax + 0x58),
                                &eax,
                                SIZE_T(4),
                                &nbr);
                if ((eax & 0x00000400) == 0) {
                    f32::float32_type x, y, w, h, dx, dy;
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3C0),
                                    &dx,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3C4),
                                    &dy,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3B4),
                                    &x,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3B8),
                                    &y,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3F0),
                                    &w,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(details::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3F4),
                                    &h,
                                    SIZE_T(4),
                                    &nbr);
                    res.emplace_back(x, y, w, h, dx, dy);
                }
            }
        }
        ebx += 0x7F0;
    }
    return res;
}

inline auto fsl_get_enemy_laser() {
    //
}

inline auto fsl_get_resources() {
    SIZE_T nbr;
    uint32_t base;
    ReadProcessMemory(details::get_process_handle(),
                     LPCVOID(0x00477818),
                     &base,
                     SIZE_T(4),
                     &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    uint32_t esi = base + 0x14;
    uint32_t ebp = esi + 0x3B0;
    ::std::vector<::std::tuple<f32::float32_type, f32::float32_type>> res{};

    for (int i = 0; i < 2000; i++)
    {
        uint32_t eax;
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
