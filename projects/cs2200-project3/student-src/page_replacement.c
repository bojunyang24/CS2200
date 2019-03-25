#include "types.h"
#include "pagesim.h"
#include "paging.h"
#include "swapops.h"
#include "stats.h"
#include "util.h"

pfn_t select_victim_frame(void);


/*  --------------------------------- PROBLEM 7 --------------------------------------
    Checkout PDF section 7 for this problem

    Make a free frame for the system to use.

    You will first call the page replacement algorithm to identify an
    "available" frame in the system.

    In some cases, the replacement algorithm will return a frame that
    is in use by another page mapping. In these cases, you must "evict"
    the frame by using the frame table to find the original mapping and
    setting it to invalid. If the frame is dirty, write its data to swap!
 * ----------------------------------------------------------------------------------
 */
pfn_t free_frame(void) {
    pfn_t victim_pfn;

    /* Call your function to find a frame to use, either one that is
       unused or has been selected as a "victim" to take from another
       mapping. */
    victim_pfn = select_victim_frame();

    /*
     * If victim frame is currently mapped, we must evict it:
     *
     * 1) Look up the corresponding page table entry
     * 2) If the entry is dirty, write it to disk with swap_write()
     * 3) Mark the original page table entry as invalid
     * 4) Unmap the corresponding frame table entry
     *
     */
    fte_t *victim_fte = (fte_t*) (frame_table + victim_pfn);
    if (victim_fte -> mapped == 1) {
        pcb_t *victim_pcb = victim_fte -> process;
        pte_t *victim_pte = ((pte_t*) (mem + (victim_pcb -> saved_ptbr * PAGE_SIZE))) + victim_fte -> vpn;
        if (victim_pte -> dirty == 1) {
            swap_write(victim_pte, (uint8_t*) (mem + (victim_pfn * PAGE_SIZE)));
            stats.writebacks += 1;
        }
        victim_pte -> valid = 0;
        victim_pte -> dirty = 0;
    }
    victim_fte -> mapped = 0; // since we are returning a free frame, we unmap it here. it will be mapped in the code that calls this function
    /* Return the pfn */
    return victim_pfn;
}



/*  --------------------------------- PROBLEM 9 --------------------------------------
    Checkout PDF section 7, 9, and 11 for this problem

    Finds a free physical frame. If none are available, uses either a
    randomized or FIFO algorithm to find a used frame for
    eviction.

    Return:
        The physical frame number of a free (or evictable) frame.

    HINTS: Use the global variables MEM_SIZE and PAGE_SIZE to calculate
    the number of entries in the frame table.
    ----------------------------------------------------------------------------------
*/
static pfn_t ptr = 0;

pfn_t select_victim_frame() {
    /* See if there are any free frames first */
    size_t num_entries = MEM_SIZE / PAGE_SIZE;
    for (size_t i = 0; i < num_entries; i++) {
        if (!frame_table[i].protected && !frame_table[i].mapped) {
            return i;
        }
    }

    if (replacement == RANDOM) {
        /* Play Russian Roulette to decide which frame to evict */
        pfn_t last_unprotected = NUM_FRAMES;
        for (pfn_t i = 0; i < num_entries; i++) {
            if (!frame_table[i].protected) {
                last_unprotected = i;
                if (prng_rand() % 2) {
                    return i;
                }
            }
        }
        /* If no victim found yet take the last unprotected frame
           seen */
        if (last_unprotected < NUM_FRAMES) {
            return last_unprotected;
        }
    } else if (replacement == FIFO) {
        /* Implement a FIFO algorithm here */
        timestamp_t curr_time = get_current_timestamp();
        timestamp_t timestamp = 0;
        pfn_t ret_pfn = 0;
        for (pfn_t i = 0; i < NUM_FRAMES; i++) {
            if (!frame_table[i].protected && (curr_time - frame_table[i].timestamp) > timestamp) {
                timestamp = curr_time - frame_table[i].timestamp;
                ret_pfn = i;
            }
        }
        if (ret_pfn == 0) {
        panic("no available pages\n");
        } else {
            return ret_pfn;
        }
    } else if (replacement == CLOCKSWEEP) {
        /* Optionally, implement the clocksweep algorithm here */
        for (pfn_t i = 0; i < 2 * NUM_FRAMES; i++) {
            if (!frame_table[ptr].protected && frame_table[ptr].timestamp == 0) {
                pfn_t ret = ptr;
                ptr = (ptr + 1) % NUM_FRAMES;
                return ret;
            }
            frame_table[ptr].timestamp = 0;
            ptr = (ptr + 1) % NUM_FRAMES;
        }
    }

    /* If every frame is protected, give up. This should never happen
       on the traces we provide you. */
    panic("System ran out of memory\n");
    exit(1);
}
