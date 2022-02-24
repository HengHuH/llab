// This file is a part of llab.

#include <Windows.h>

#include "ll_driver.h"
#include "resource.h"

#define CLASS_NAME L"HENG_LLAB"
#define TITLE_NAME L"LLab"

struct Window
{
    HWND hwnd;
    int should_close;
} window;

int w = 900;
int h = 600;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY)
    {
        window.should_close = 1;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void ll_driver_run()
{
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    const HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN));

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
        .lpszClassName = CLASS_NAME,
        .hIconSm = icon};

    if (!RegisterClassEx(&wcex))
    {
        MessageBoxW(NULL, L"Failed to create window.", L"Error", MB_OK);
        ExitProcess(127);
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        TITLE_NAME,
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
    window.hwnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);

    // RUN
    MSG msg = {0};
    while (!window.should_close)
    {
        while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0)
        {
            if (msg.message == WM_DESTROY)
            {
                PostQuitMessage(0);
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        SleepEx(0, TRUE);
    }
}