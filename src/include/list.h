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

extern amw_list_t *amw_list_new(void);
extern amw_list_node *amw_list_new_node(void *data);
extern amw_list_node *amw_list_append_node(amw_list_t *list, amw_list_node *n);
extern amw_list_node *amw_list_prepend_node(amw_list_t *list, amw_list_node *n);
extern amw_list_node *amw_list_insert_after(amw_list_node *after, amw_list_node *n);
extern amw_list_node *amw_list_insert_before(amw_list_node *before, amw_list_node *n);
extern amw_list_node *amw_list_add(amw_list_t *list, amw_list_node *n);
extern void amw_list_del(amw_list_t *list, amw_list_node *n);
extern void amw_list_pop(amw_list_t *list);
extern void amw_list_shift(amw_list_t *list);

#endif /* __AMW_LIST_H */
