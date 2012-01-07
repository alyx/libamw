#include "amw.h"

amw_list_t *amw_list_new(void)
{
    amw_list_t *new;
    new = malloc(sizeof(amw_list_t));
    new->head = NULL;
    new->tail = NULL;

    return new;
}

amw_list_node *amw_list_new_node(void *data)
{
    amw_list_node *n;
    n = malloc(sizeof(amw_list_node));
    n->prev = NULL;
    n->next = NULL;
    n->data = data;

    return n;
}

amw_list_node *amw_list_append_node(amw_list_t *list, amw_list_node *n)
{
    if ((n == NULL) || (list == NULL))
        return NULL;

    n->next = NULL;
    if (list->tail != NULL)
    {
        list->tail->next = n;
        n->prev = list->tail;
        list->tail = n;
    }
    else
        list->tail = n;

    if (list->head == NULL)
        list->head = n;

    return n;
}

amw_list_node *amw_list_prepend_node(amw_list_t *list, amw_list_node *n)
{
    if ((n == NULL) || (list == NULL))
        return NULL;

    if (list->head == NULL)
        list->head = n;
    else
    {
        n->next = list->head;
        list->head = n;
    }

    return n;
}

amw_list_node *amw_list_insert_after(amw_list_node *after, amw_list_node *n)
{
    if (n->prev != NULL)
        n->prev->next = n->next;

    if (!after)
        return NULL;

    n->prev = after;
    n->next = after->next;
    after->next = n;

    return n;
}

amw_list_node *amw_list_insert_before(amw_list_node *before, amw_list_node *n)
{
    if ((before == NULL) || (n == NULL))
        return NULL;

    n->prev = before->prev;
    n->next = before;
    before->prev = n;

    return n;
}

amw_list_node *amw_list_add(amw_list_t *list, amw_list_node *n)
{
    return amw_list_append_node(list, n);
}

void amw_list_del(amw_list_t *list, amw_list_node *n)
{
    amw_list_node *tn;

    if ((n == NULL) || (list == NULL))
        return;

    if (list->head == n)
    {
        list->head = n->next;
        list->head->prev = NULL;
    }
    
    n->prev->next = n->next;
}

void amw_list_pop(amw_list_t *list)
{
    amw_list_del(list, list->head);
}

void amw_list_shift(amw_list_t *list)
{
    amw_list_del(list, list->tail);
}

