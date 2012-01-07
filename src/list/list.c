#include "list.h"
#include <stdlib.h>
#ifdef AMW_LIST_TEST
#include <stdio.h>
#endif

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


#ifdef AMW_LIST_TEST
void amw_list_printlist(amw_list_t *list)
{
    amw_list_node *n;
    n = list->head;
    if (n == NULL)
        printf("WTF? Head is NULL!\n");

    while (n)
    {
        printf("%d ", *(int *)n->data);
        n = n->next;
    }
    printf("\n");
}

void amw_list_printlist_backwards(amw_list_t *list)
{
    amw_list_node *n;
    n = list->tail;
    if (n == NULL)
        printf("WTF? Tail is NULL!\n");

    while (n)
    {
        printf("%d ", *(int *)n->data);
        n = n->prev;
    }
    printf("\n");
}

int main(void)
{
    int i;
    amw_list_t *testlist;
    amw_list_node *n;
    testlist = amw_list_new();
    int data[] = {8,0,7,2,5,3,6,9,4,1};
    for(i = 0; i < sizeof(data)/sizeof(data[0]); i++)
    {
        printf("Adding %d...\n", data[i]);
        n = amw_list_new_node(&data[i]);
        amw_list_append_node(testlist, n);
    }
    n = testlist->head->next->next;
    printf("n: %d\n", *(int *)n->data);
    amw_list_printlist(testlist);
    amw_list_del(testlist, n);
    printf("Forwards: ");
    amw_list_printlist(testlist);
    printf("Backwards: ");
    amw_list_printlist_backwards(testlist);

    return 0;
}

#endif
