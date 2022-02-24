#include <stdio.h>

#include <Windows.h>

static int quit = 0;

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY)
    {
        quit = 1;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *lpCmdLine, int nCmdShow)
{
    printf("Hello llab console.\n");

    WNDCLASSEX wcex = {
        .cbSize = sizeof(WNDCLASSEXW),
        .style = CS_DBLCLKS,
        .lpfnWndProc = (WNDPROC)WindowProc,
        .cbClsExtra = 0,
        .cbWndExtra = 0,
        .hInstance = hInstance,
        .hIcon = NULL,
        .hCursor = LoadCursor(NULL, IDC_ARROW),
        .hbrBackground = NULL,
        .lpszMenuName = NULL,
        .lpszClassName = L"Heng",
        .hIconSm = NULL};

    if (!RegisterClassEx(&wcex))
    {
        MessageBoxW(NULL, L"Failed to create window.", L"Error", MB_OK);
        ExitProcess(127);
    }

    HWND hwnd = CreateWindowEx(
        0,
        L"Heng",
        L"Hlab",
        (WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_BORDER),
        0, 0, 900, 600,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (!hwnd)
    {
        MessageBox(NULL, L"Failed to create window.", L"Error", MB_OK);
        ExitProcess(127);
    }
    ShowWindow(hwnd, SW_SHOW);

    // RUN
    MSG msg = {0};
    while (!quit)
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
    return 0;
}