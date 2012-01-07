#include <time.h>
#include <signal.h>
#include <unistd.h>
#include "amw_timer.h"

static amw_timer_list_t *events;
static time_t next_event;

void amw_timer_init(void)
{
    signal(SIGALARM, amw_timer_handle_alarm);
}

static void amw_timer_handle_alarm(int signal)
{
    unsigned int count;
    amw_timer_event_t *event;
    amw_timer_list_node *node;
    time_t now;
    now = time(NULL);
    count = 0;
    amw_timer_LIST_FOREACH(events, node)
    {
        event = (amw_timer_event_t *)node->data;
        if (event->runtime <= now)
        {
            event->handle(event->udata);
            count++;
            if (event->repeat == true)
                event->runtime = (now + event->wait);
            else
                amw_timer_del(node);
        }
    }
    return count;
}


void amw_timer_set_alarm(time_t runtime)
{
    next_event = runtime;
    alarm(next_event);
}

void amw_timer_check_events(void)
{
    amw_timer_list_node *node;
    amw_timer_event_t *event;
    time_t shortest;
    shortest = next_event;
    amw_timer_LIST_FOREACH(events, node)
    {
        event = (amw_timer_event_t *)node->data;
        if (event->runtime < shortest)
            shortest = event->runtime;
    }
        if (shortest != next_event)
            amw_timer_set_alarm(shortest);
}     

time_t amw_timer_add(amw_timer_function_t handle, void *udata, int8_t wait)
{
    amw_timer_event_t *event;
    time_t runtime;
    runtime = (time(NULL) + wait);
    event = malloc(sizeof(amw_timer_event_t));
    event->handle = handle;
    event->runtime = runtime;
    event->udata = udata;

    amw_timer_list_add(events, &event);

    amw_timer_check_events();

    return runtime;
}


