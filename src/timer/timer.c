#include <time.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>
#include "timer.h"

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
    for(node = events->head; node != NULL; node = node->next)
    {
        event = (amw_timer_event_t *)node->data;
        if (event->runtime <= now)
        {
            event->handle(event->udata);
            /* XXX: Deal with repeat logic later.
            if (event->repeat == true)
                event->runtime = (now + event->wait);
            else
            */
                amw_timer_del(node);
        }
        else
        {
            amw_timer_set_alarm(event->runtime);
            break;
        }
    }
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

void amw_timer_del(amw_list_node *n)
{
    amw_timer_event_t *event;
    event = (amw_timer_event_t *)n->data;
    free(event);
    amw_list_del(events, n);
}

time_t amw_timer_add(amw_timer_function_t handle, void *udata, 
        int8_t wait, bool repeat)
{
    amw_timer_event_t *event, *listed;
    amw_list_node *n;
    time_t runtime;
    bool added;
    runtime = (time(NULL) + wait);
    event = malloc(sizeof(amw_timer_event_t));
    event->handle = handle;
    event->repeat = repeat;
    event->wait = wait;
    event->runtime = runtime;
    event->udata = udata;

    n = events->head;
    for(n = event->head; ((n != NULL) && (added == false)); n = n->next)
    {
        listed = (amw_timer_event_t *)n->data;
        if (event->runtime < listed->runtime)
        {
            amw_list_insert_before(listed, event);
            added = true;
            amw_timer_set_alarm(event->runtime);
        }
    }
    if (added == false)
        amw_list_append_node(events, event);
    if (!(next_event))
        amw_timer_set_alarm(event->runtime);

    return runtime;
}


