#include <stdio.h>
#include <string.h>

#include "swap.h"
#include "util.h"

static uint64_t TOKEN = 1;

swap_info_t *create_entry(void)
{
    swap_info_t *new_info = calloc(1, sizeof(swap_info_t));
    if (!new_info) {
        panic("could not allocate swap entry");
    }
    new_info->token = TOKEN++;
    return new_info;
}

void swap_queue_enqueue(swap_queue_t *queue, swap_info_t* info)
{
    info->next = NULL;
    if (queue->head == NULL) {
        queue->head = queue->tail = info;
    } else {
        queue->tail->next = info;
        queue->tail = info;
    }
    queue->size++;
    if (queue->size > queue->size_max) {
        queue->size_max = queue->size;
    }
}


void swap_queue_dequeue(swap_queue_t *queue, uint64_t token)
{
    swap_info_t *curr = queue->head;
    swap_info_t *prev = NULL;

    while (curr) {
        if (curr->token == token) {
            if (prev) {
                prev->next = curr->next;
            } else {
                queue->head = curr->next;
            }
            if (curr == queue->tail) {
                queue->tail = prev;
            }
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    queue->size--;
    curr->next = NULL;
    free(curr);
}

swap_info_t *swap_queue_find(swap_queue_t *queue, uint64_t token)
{
    swap_info_t *curr = queue->head;

    while (curr) {
        if (curr->token == token) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
