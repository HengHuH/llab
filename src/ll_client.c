// This file is a part of llab.

#include <stdio.h>

#include "ll_engine.h"
#include "ll_client.h"

static void init()
{
    ll_engine_init();
}

static void post_init()
{
    ll_engine_post_init();
}

static void pre_tick()
{
    printf("Client: pre tick.\n");
}

static void start()
{
    // before first frame
    ll_engine_first_frame();
}

static void pre_run()
{
    init();
    post_init();
    start();
    pre_tick();

    ll_engine_enter();
}

static void post_tick()
{
}

static void stop()
{
    ll_engine_last_frame();
}

static void finalize()
{
    printf("Client: finalize.\n");
    ll_engine_finalize();
}

static void post_run()
{
    ll_engine_shutdowm_frame();
    ll_engine_leave();

    post_tick();
    stop();
    finalize();
}

void ll_client_preinit()
{
    printf("Client: preinit.\n");
}

void ll_client_run()
{
    printf("Client: run.\n");
    pre_run();
    {
        ll_engine_tick_loop();
    }
    post_run();
}

void ll_client_mark_close()
{
    ll_engine_mark_close();
}
