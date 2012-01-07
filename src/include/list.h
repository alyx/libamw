#ifndef __AMW_LIST_H
#define __AMW_LIST_H

//#define amw_list_t_FOREACH(head, node) for(node = head; node->next != NUamw_list; node = node->next)

typedef struct _amw_list_node amw_list_node;
typedef struct _amw_list_ amw_list_t;

struct _amw_list_node {
    amw_list_node *prev, *next;
    void *data;
} _amw_list_node;

struct _amw_list_ {
    amw_list_node *head, *tail;
} _amw_list_t;

#endif /* __AMW_LIST_H */
