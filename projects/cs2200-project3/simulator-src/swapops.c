#include "swapops.h"
#include "util.h"

swap_queue_t swap_queue;

void swap_read(pte_t *pte, void *dst) {

    swap_info_t *info = swap_queue_find(&swap_queue, pte->swap);
    if (!info) {
        panic("Attempted to read an invalid swap entry.\nHINT: How do you check if a swap entry exists, and if it does not, what should you put in memory instead?");
    }
    memcpy(dst, info->page_data, PAGE_SIZE);
}

void swap_write(pte_t *pte, void *src) {

    swap_info_t *info = swap_queue_find(&swap_queue, pte->swap);
    if (!info) {
        info = create_entry(); // creates a swap entry and assigns a token
        swap_queue_enqueue(&swap_queue, info);
        pte->swap = info->token;
    }
    memcpy(info->page_data, src, PAGE_SIZE);
}

void swap_free(pte_t *pte) {
    swap_entry_t swp_entry = pte->swap;
    if (!swap_queue_find(&swap_queue, swp_entry)) {
        panic("Attempted to free an invalid swap entry!");
    }
    swap_queue_dequeue(&swap_queue, pte->swap);
    pte->swap = 0;
}
