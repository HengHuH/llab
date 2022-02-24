// This file is a part of llab.

#include <Windows.h>

#include "ll_client.h"
#include "ll_driver.h"

#define CLASS_NAME L"HENG_LLAB"
#define TITLE_NAME L"LLab"

struct Window
{
    HWND hwnd;
    int should_close;
} window;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY)
    {
        ll_client_mark_close();
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static HWND create_window(const WCHAR *class_name, const WCHAR *title_name, const HICON icon, int w, int h)
{
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    WNDCLASSEX wcex = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_DBLCLKS,
        .lpfnWndProc = (WNDPROC)WindowProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = icon,
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = NULL,
        .lpszMenuName = NULL,
        .lpszClassName = class_name,
        .hIconSm = icon};

    if (!RegisterClassEx(&wcex))
    {
        MessageBoxW(NULL, L"Failed to create window.", L"Error", MB_OK);
        ExitProcess(127);
    }

    HWND hwnd = CreateWindowEx(
        0,
        class_name,
        title_name,
        (WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_BORDER),
        0, 0, w, h,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hwnd)
    {
        MessageBox(NULL, L"Failed to create window.", L"Error", MB_OK);
        ExitProcess(127);
    }

    window.should_close = 0;
    ShowWindow(hwnd, SW_HIDE);

    return hwnd;
}

void ll_driver_run(const WCHAR *class_name, const WCHAR *title_name, const HICON icon)
{
    window.hwnd = create_window(class_name, title_name, icon, 900, 600);
    ShowWindow(window.hwnd, SW_SHOW);
    // ll_client_preinit();
    ll_client_run();
}