/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    /* What if malloc returned NULL? */
    if (q == NULL)
    {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }

    /* How about freeing the list elements and the strings? */
    list_ele_t *curr = q->head;
    list_ele_t *temp;
    while (curr != NULL)
    {
        temp = curr->next;
        free(curr->value);
        free(curr);
        curr = temp;
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
    {
        return false;
    }

    /* Create new node. */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
    {
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL)
    {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    /* What if either call to malloc returns NULL? */
    if (q->head == NULL)
    {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
    {
        return false;
    }

    /* Create new node. */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
    {
        return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL)
    {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    if (q->head == NULL)
    {
        q->head = newh;
        q->tail = newh;
    }
    else
    {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->tail->next = NULL;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->head == NULL)
    {
        return false;
    }

    list_ele_t *newh = q->head->next;
    list_ele_t *currh = q->head;

    /* Copy str. */
    if (sp != NULL && currh->value != NULL)
    {
        strncpy(sp, currh->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    /* Free space. */
    free(currh->value);
    free(currh);

    q->head = newh;
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL)
    {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
    {
        return;
    }

    list_ele_t *currh = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    while (curr != NULL)
    {
        list_ele_t *temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    q->head = prev;
    q->tail = currh;
}
