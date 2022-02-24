#include <stdio.h>

#include <Windows.h>

#include "ll_driver.h"


// Win32 entry main.
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *lpCmdLine, int nCmdShow)
{
    printf("Hello llab console.\n");

    // start driver
    ll_driver_run();
    // init engine
    return 0;
}