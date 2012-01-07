#ifndef __AMW_TIMER_H
#define __AMW_TIMER_H

#include <stdbool.h>
#include "list.h"

typedef void (*amw_timer_function_t)(void *udata);

typedef struct _amw_timer_timed_event
{
    amw_timer_function_t handle;
    bool repeat;
    time_t wait;
    time_t runtime;
    void *udata;
} amw_timer_event_t;


#endif
