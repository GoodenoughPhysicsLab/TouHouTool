#pragma once

#include <cstdint>
#include <cstddef>
#include <Windows.h>
#include <windef.h>
#include <winuser.h>
#include <gdiplus.h>
#include <opencv2/opencv.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "bind.hh"

#pragma comment (lib,"gdiplus.lib")
#pragma comment (lib,"gdi32.lib")

namespace py = pybind11;

namespace thtool::details {



} // namespace thtool::details

namespace thtool::window {

[[nodiscard]] inline auto& get_size() {
    struct TH_Screen {
        decltype(tagRECT::right) width = 0;
        decltype(tagRECT::bottom) height = 0;
    };
    static TH_Screen res{};

    if (res.height != 0 && res.width != 0) {
        return res;
    }

    RECT rect;
    if (GetClientRect(thtool::bind::TH_hwnd.value(), &rect)) {
        res.width = rect.right;
        res.height = rect.bottom;
        if (res.width == 0 || res.height == 0) {
            PyErr_SetString(PyExc_RuntimeError,
                    "get screen width or height fail, try to click your TouHou window to solve it");
            throw py::error_already_set();
        }
    }
    return res;
}

inline py::array_t<uint8_t> get_scene() {
    auto screen = get_size();

    // init
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // compute
    HDC hScreenDC = GetDC(thtool::bind::TH_hwnd.value()); // never will fail(return NULL)
                                                                // because get_size have checked
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screen.width, screen.height);
    HGDIOBJ old_obj = SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, screen.width, screen.height,
        hScreenDC, 0, 0, SRCCOPY);
    Gdiplus::Bitmap bitmap(hBitmap, NULL);

    ::std::size_t size = screen.width * screen.height * 4;
    std::unique_ptr<uint8_t[]> buffer(new uint8_t[size]);

    Gdiplus::Rect rect(0, 0, screen.width, screen.height);
    Gdiplus::BitmapData bitmapData;
    bitmap.LockBits(&rect, Gdiplus::ImageLockModeRead,
                    PixelFormat24bppRGB, &bitmapData);

    memcpy(buffer.get(), bitmapData.Scan0, size);

    bitmap.UnlockBits(&bitmapData);

    // free resource
    SelectObject(hMemoryDC, old_obj);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    Gdiplus::GdiplusShutdown(gdiplusToken);

    py::array_t<uint8_t> result({screen.height, screen.width, 4}, buffer.release());
}

} // namespace thtool::window