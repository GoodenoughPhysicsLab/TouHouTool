#pragma once

#include <cstddef>
#include <Windows.h>
#include <windef.h>
#include <winuser.h>
#include <gdiplus.h>
#include <pybind11/pybind11.h>
#include "bind.hh"

#pragma comment (lib,"gdiplus.lib")
#pragma comment (lib,"gdi32.lib")

namespace py = pybind11;

namespace thtool::details {

inline ULONG_PTR gdiplusToken;

inline BOOL GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0, size = 0;
    Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

    Gdiplus::GetImageEncodersSize(&num, &size);
    if (size == 0) {
        return FALSE;
    }

    pImageCodecInfo = (Gdiplus::ImageCodecInfo*)malloc(size);
    if (pImageCodecInfo == NULL) {
        return FALSE;
    }

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return TRUE;
        }
    }

    free(pImageCodecInfo);
    return FALSE;
}

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

#if 0
// return the screen scene instead of saving image
inline py::array_t<uint8_t> get_scene() { // TODO
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

    ::std::size_t res_size = screen.width * screen.height * 4;
    py::array_t<uint8_t> res(res_size);

    // lock bitmap
    Gdiplus::Rect rect(0, 0, screen.width, screen.height);
    Gdiplus::BitmapData bitmapData;
    auto status = bitmap.LockBits(&rect, Gdiplus::ImageLockModeRead,
                    PixelFormat24bppRGB, &bitmapData);

    memcpy(res.mutable_data(0), bitmapData.Scan0, res_size);

    bitmap.UnlockBits(&bitmapData);

    // free resource
    SelectObject(hMemoryDC, old_obj);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return res;
}
#endif

inline void init_Gdiplus() {
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&details::gdiplusToken, &gdiplusStartupInput, NULL);
}

inline void save_scene_img() {
    auto [width, height] = get_size();

    HDC hScreenDC = GetDC(thtool::bind::TH_hwnd.value());
    if (hScreenDC == NULL) {
        throw bind::BindError("invalid handle");
    }
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    HGDIOBJ old_obj = SelectObject(hMemoryDC, hBitmap);
    BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);

    CLSID clsid;
    details::GetEncoderClsid(L"image/bmp", &clsid);

    Gdiplus::Bitmap bitmap(hBitmap, NULL);
    bitmap.Save(L"C:\\Windows\\Temp\\thtemp.bmp", &clsid, NULL);

    SelectObject(hMemoryDC, old_obj);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);
}

inline void free_Gdiplus() {
    Gdiplus::GdiplusShutdown(details::gdiplusToken);
}

inline bool is_foreground_window() {
    return bind::TH_hwnd.value() == GetForegroundWindow();
}

} // namespace thtool::window