// This file is a part of llab.

#include <stdio.h>
#include <Windows.h>  // TODO: (heng) remove me later.

#include "ll_engine.h"

static int should_close = 0;

void ll_engine_init()
{
    printf("Engine: init.\n");
}

void ll_engine_finalize()
{
    printf("Engine: finalize.\n");
}

void ll_engine_post_init()
{
    printf("Engine: post init.\n");
}

void ll_engine_first_frame()
{
    printf("Engine: first frame.\n");
}

void ll_engine_last_frame()
{
    printf("Engine: last frame.\n");
}

void ll_engine_shutdowm_frame()
{
    printf("Engine: shutdown frame.\n");
}

void ll_engine_enter()
{
    printf("Engine: enter.\n");
}

void ll_engine_tick_loop()
{
    printf("Engine: tick loop.\n");
    MSG msg = {0};
    while (!should_close)
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

void ll_engine_leave()
{
    printf("Engine: leave.\n");
}

void ll_engine_mark_close()
{
    should_close = 1;
}