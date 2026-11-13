/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t)); //
    /* What if malloc returned NULL? */
    if (q == NULL){
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    //if q is null -> nothing, if q is not null -> go to next
    if (q == NULL){
        return;
    }
    //to be freed: The queue, the nodes inside the queue, the value inside the nodes
    // if have node -> go into loop, if not-> just free the queue
    list_ele_t *current = q->head;
    while (current != NULL){
        // free the value of node + node
        // if have next node-> current = next, if no next node -> current = null -> end
        list_ele_t *temp = current->next;
        free(current->value);
        free(current);
        
        current = temp;
    }

    //free the queue
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL){
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL){
        return false;
    }

    //node initialize
    newh->value = NULL;
    newh->next = q->head;
    if (s != NULL){
        newh->value = malloc(strlen(s)+1);
        if (newh->value == NULL){
            free(newh);
            return false;
        }
        strcpy(newh->value,s);
    }

    //add node into q
    if (q->head == NULL){
        q->tail = newh;
    }
    q->head = newh;
    q->length++;
    
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    /* What should you do if the q is NULL? */
    if (q == NULL){
        return false;
    }
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL){
        return false;
    }

    //node initialization
    newt->value = NULL;
    newt->next = NULL;
    if (s != NULL){
        newt->value = malloc(strlen(s)+1);
        if (newt->value == NULL){
            free(newt);
            return false;
        }
        strcpy(newt->value,s);
    }

    //add the node into q
    if (q->tail == NULL){
        q->head = newt;
    }
    else{
        q->tail->next = newt;
    }
    q->tail = newt;
    q->length++;   

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    //remove
    if (q == NULL){
        return false;
    }
    if (q->head == NULL){
        return false;
    }
    //remove head node from q
    list_ele_t *temp = q->head;
    if (q->length == 1){
        q->tail = NULL;
    }
    q->head = q->head->next;
    q->length--;

    //copy
    //if buf = NULL-> no need copy, just free memory
    //if buf not NULL-> (if value is NULL->do  nothing , else if value not NULL-> copy+free) + free memory
    if (buf != NULL && temp->value != NULL){
        size_t maxsize = bufsize-1;
        if (strlen(temp->value) < maxsize ){
            maxsize = strlen(temp->value);
        }
        for (size_t i=0;i<maxsize;i++){
            buf[i] = temp->value[i];
        }
        buf[maxsize] = '\0';
    }

    //free
    free(temp->value);
    free(temp);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL){
        return 0;
    }
    return q->length;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL){
        return;
    }
    if (q->head == NULL){
        return;
    }
    list_ele_t *previous = q->head;
    list_ele_t *current = previous->next;
    list_ele_t *next;
    while (current != NULL){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    q->head->next = NULL;
    q->tail = q->head;
    q->head = previous;
}
