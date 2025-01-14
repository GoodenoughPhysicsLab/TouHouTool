#pragma once

#include <windows.h>
#include <basetsd.h>
#include <cstdint>
#include <memoryapi.h>
#include <tuple>
#include <string_view>
#include <vector>
#include <windef.h>
#include "float32.hh"
#include "process.hh"

namespace auto_th10::readmem {

class GameNotStartError : public ::std::exception {
    ::std::string_view err_msg{"game not start(don't means touhou window not open)"};
public:
    inline GameNotStartError() noexcept = default;
    ~GameNotStartError() = default;

    inline const char* what() const noexcept override {
        return err_msg.data();
    }
};

/* Note:
 *   this file get position by read memory
 *   but, it's not the position on screen
 *   the code thansform it to screen position is in thtool/scene.py
 */

#ifdef _MSC_VER
#pragma warning(disable: 4312)
#endif

inline auto get_player() {
    float32_type x, y;
    uint32_t obj_base{};
    SIZE_T nbr;
    ReadProcessMemory(process::get_process_handle(),
                      LPCVOID(0x00477834),
                      &obj_base,
                      SIZE_T(4),
                      &nbr);
    if (obj_base == 0) {
        throw GameNotStartError();
    }
    ReadProcessMemory(process::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C0),
                      &x,
                      SIZE_T(4),
                      &nbr);
    ReadProcessMemory(process::get_process_handle(),
                      reinterpret_cast<LPCVOID>(obj_base + 0x3C4),
                      &y,
                      SIZE_T(4),
                      &nbr);

    return ::std::make_tuple(x, y);
}

inline auto get_enemies() {
    SIZE_T nbr;
    uint32_t base{}, obj_base{}, obj_addr, obj_next{};

    ReadProcessMemory(process::get_process_handle(),
                      LPCVOID(0x00477704),
                      &base,
                      SIZE_T(4),
                      &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    ReadProcessMemory(process::get_process_handle(),
                      reinterpret_cast<LPCVOID>(base + 0x58),
                      &obj_base,
                      SIZE_T(4),
                      &nbr);

    ::std::vector<::std::tuple<float32_type,
                                float32_type,
                                float32_type,
                                float32_type>> res{};
    if (obj_base) {
        while (true)
        {
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_base),
                              &obj_addr,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_base + 4),
                              &obj_next,
                              SIZE_T(4),
                              &nbr);
            obj_addr += 0x103C;
            uint32_t t;
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(obj_addr + 0x1444),
                              &t,
                              SIZE_T(4),
                              &nbr);
            if ((t & 0x40) == 0) {
                ReadProcessMemory(process::get_process_handle(),
                                  reinterpret_cast<LPCVOID>(obj_addr + 0x1444),
                                  &t,
                                  SIZE_T(4),
                                  &nbr);
                if ((t & 0x12) == 0) {
                    float32_type x, y, w, h;
                    ReadProcessMemory(process::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0x2C),
                                      &x,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0x30),
                                      &y,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                      reinterpret_cast<LPCVOID>(obj_addr + 0xB8),
                                      &w,
                                      SIZE_T(4),
                                      &nbr);
                    ReadProcessMemory(process::get_process_handle(),
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

inline auto get_enemy_bullets() {
    uint32_t base{};
    SIZE_T nbr;
    ReadProcessMemory(process::get_process_handle(),
                    LPCVOID(0x004776F0),
                    &base,
                    SIZE_T(4),
                    &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    uint32_t ebx = base + 0x60;
    ::std::vector<::std::tuple<float32_type,
                                float32_type,
                                float32_type,
                                float32_type,
                                float32_type,
                                float32_type>> res{};
    for (int _{}; _ < 2000; ++_)
    {
        uint32_t edi = ebx + 0x400;
        uint32_t bp{};
        ReadProcessMemory(process::get_process_handle(),
                        reinterpret_cast<LPCVOID>(edi + 0x46),
                        &bp,
                        SIZE_T(4),
                        &nbr);
        bp &= 0x0000FFFF;
        if (bp) {
            uint32_t eax{};
            ReadProcessMemory(process::get_process_handle(),
                            reinterpret_cast<LPCVOID>(0x477810),
                            &eax,
                            SIZE_T(4),
                            &nbr);
            if (eax) {
                ReadProcessMemory(process::get_process_handle(),
                                reinterpret_cast<LPCVOID>(eax + 0x58),
                                &eax,
                                SIZE_T(4),
                                &nbr);
                if ((eax & 0x00000400) == 0) {
                    float32_type x, y, w, h, dx, dy;
                    ReadProcessMemory(process::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3C0),
                                    &dx,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3C4),
                                    &dy,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3B4),
                                    &x,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3B8),
                                    &y,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(process::get_process_handle(),
                                    reinterpret_cast<LPCVOID>(ebx + 0x3F0),
                                    &w,
                                    SIZE_T(4),
                                    &nbr);
                    ReadProcessMemory(process::get_process_handle(),
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

inline auto get_enemy_lasers() {
    uint32_t base{};
    SIZE_T nbr;
    ReadProcessMemory(process::get_process_handle(),
                    LPCVOID(0x0047781C),
                    &base,
                    SIZE_T(4),
                    &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }

    uint32_t esi{}, ebx{};
    ReadProcessMemory(process::get_process_handle(),
                      reinterpret_cast<LPCVOID>(base + 0x18),
                      &esi,
                      SIZE_T(4),
                      &nbr);

    ::std::vector<::std::tuple<float32_type,
                                float32_type,
                                float32_type,
                                float32_type,
                                float32_type>> res{};
    if (esi)
    {
        while (true)
        {
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x8),
                              &ebx,
                              SIZE_T(4),
                              &nbr);
            float32_type x, y, h, w, arc;
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x24),
                              &x,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x28),
                              &y,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x3C),
                              &arc,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x40),
                              &h,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(esi + 0x44),
                              &w,
                              SIZE_T(4),
                              &nbr);
            res.emplace_back(x, y, w, h, arc);
            if (ebx == 0) {
                break;
            }
            esi = ebx;
        }
    }
    return res;
}

inline auto get_resources() {
    SIZE_T nbr;
    uint32_t base;
    ReadProcessMemory(process::get_process_handle(),
                     LPCVOID(0x00477818),
                     &base,
                     SIZE_T(4),
                     &nbr);
    if (base == 0) {
        throw GameNotStartError();
    }
    uint32_t esi = base + 0x14;
    uint32_t ebp = esi + 0x3B0;
    ::std::vector<::std::tuple<float32_type, float32_type>> res{};

    for (int i = 0; i < 2000; i++)
    {
        uint32_t eax;
        ReadProcessMemory(process::get_process_handle(),
                          reinterpret_cast<LPCVOID>(ebp + 0x2C),
                          &eax,
                          SIZE_T(4),
                          &nbr);
        if (eax != 0) {
            float32_type x, y;
            ReadProcessMemory(process::get_process_handle(),
                              reinterpret_cast<LPCVOID>(ebp - 0x4),
                              &x,
                              SIZE_T(4),
                              &nbr);
            ReadProcessMemory(process::get_process_handle(),
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

inline auto get_score() noexcept {
    ::std::uint32_t score;
    ReadProcessMemory(
        process::get_process_handle(),
        reinterpret_cast<LPCVOID>(0x00474C44),
        &score,
        SIZE_T(4),
        nullptr
    );
    return score;
}

inline auto get_power() noexcept {
    ::std::uint16_t power;
    ReadProcessMemory(
        process::get_process_handle(),
        reinterpret_cast<LPCVOID>(0x00474C48),
        &power,
        SIZE_T(sizeof(power)),
        nullptr
    );
    return power;
}

/* Get Player's HP
 */
inline auto get_hp() noexcept {
    ::std::uint16_t hp;
    ReadProcessMemory(
        process::get_process_handle(),
        reinterpret_cast<LPCVOID>(0x00474C70),
        &hp,
        SIZE_T(sizeof(hp)),
        nullptr
    );
    return hp;
}

#ifdef _MSC_VER
#pragma warning(default: 4312)
#endif

} // namespace auto_th10::readmem
