#include "../include/linked_list.h"
/*
 * Linked list
 */

#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

/* functions to create lists */
node *make_node(int v, node *q)
{
  node *p = malloc(sizeof(node));
  p->value = v;

  if (q == &SENTINEL_node)
    p->next = &SENTINEL_node;
  else
    p->next = q;
  return p;
}

/* free all nodes in the list p */
// problem with sentinel nodes having different addresses here and in main.cpp
// p will point to something random after this, not sentinel. So SegFaults.
// void free_list(node *p)
// {
//   node *q = p;
//   while (q != &SENTINEL_node)
//   {
//     node *t = q->next;
//     free(q);
//     q = t;
//   }
// }

// this deletes everything and sets to null. Would have the advantage of not using memory for a sentinel node, but oh well.
void free_list(node **p)
{
  node *q = *p;
  while (q->next != NULL)
  {
    node *t = q->next;
    free(q);
    q = t;
  }
  (*p) = NULL;
}

/* print list to console */
void print_list(node *p)
{
  if (p == NULL)
    return;
  else
  {
    printf("%d ", p->value);
    print_list(p->next);
  }
}

int sum_squares(node *p)
{
  if (p == NULL)
    return 0;
  else
    return (p->value * p->value + sum_squares(p->next));
}

int square(int x)
{
  return x * x;
}

node *map(node *p, int (*f)(int))
{
  if (p == NULL)
    return NULL;
  else
  {
    node *item = malloc(sizeof(node));
    item->value = f(p->value);
    item->next = map(p->next, f);
    return item;
  }
}
