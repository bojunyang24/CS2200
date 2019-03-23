#pragma once

#include "pagesim.h"
#include "types.h"

typedef uint64_t swap_entry_t;

typedef struct swap_info {

    uint64_t token;
    uint8_t  page_data[PAGE_SIZE];

    struct swap_info *next;
} swap_info_t;

typedef struct _swap_queue_t {
    swap_info_t *head;
    swap_info_t *tail;
    uint64_t size;
    uint64_t size_max;
} swap_queue_t;

swap_info_t *create_entry(void);
void swap_queue_enqueue(swap_queue_t *queue, swap_info_t* info);
void swap_queue_dequeue(swap_queue_t *queue, uint64_t token);
swap_info_t *swap_queue_find(swap_queue_t *queue, uint64_t token);
