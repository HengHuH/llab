// This file is a part of llab.

#include <stdio.h>

#include <Windows.h>
#include "resource.h"

#include "ll_driver.h"


// Win32 entry main.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *lpCmdLine, int nCmdShow)
{
    printf("Hello llab console.\n");

    WCHAR* class_name = L"Heng_LLab";
    WCHAR* title_name = L"LLab - Heng -";
    const HICON icon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN));
    // start driver
    ll_driver_run(class_name, title_name, icon);
    // init engine
    return 0;
}