#pragma once

#include "swap.h"
#include "types.h"
#include "pagesim.h"
#include "page_splitting.h"

/*
 * An entry in the page table.
 *
 * A page table maps indices (often referred to as virtual page numbers, or
 * VPNs) to corresponding physical frames in memory. Note that the VPN is not
 * stored in the entry - it's the index into the page table!
 */
typedef struct ptable_entry {
    uint8_t valid;              /* 1 if the entry is mapped to a valid frame, 0
                                   otherwise */
    uint8_t dirty;              /* 1 if the entry has been modified from its
                                   form on disk and must be written back when it
                                   is next evicted. */
    pfn_t pfn;                 /* The physical frame number (PFN) this entry
                                   maps to. */
    swap_entry_t swap;          /* The swap entry mapped to this page. Use this
                                   to read to/write from the page to disk using
                                   swap_read() and swap_write() */
} pte_t;

/*
 * An entry in the frame table.
 *
 * When we need a new physical frame, we must have some way to know which frames
 * are free. The frame table does just this. It is a global table shared among
 * all processes, and contains one entry for each physical frame on the disk.
 *
 * Frames come in one of two forms: Either they hold memory system data (such as
 * a page directory or page table), or they hold data for a page mapped via a
 * page table.
 *
 * Whenever you allocate or re-purpose frames, you *MUST* keep the frame table
 * up to date. You'll read from the frame table in page_replacement.c to select
 * which frames to hand out when processes require more pages.
 */
typedef struct ft_entry {
    /* -- Used for page table pages -- */
    uint8_t protected;          /* 1 if the frame holds a page table and is
                                   immune from eviction, 0 otherwise */
    /* -- Used for data pages -- */
    uint8_t mapped;             /* 1 if the frame is mapped, 0
                                   otherwise */
    timestamp_t timestamp;      /* 32 bit number that represents the last time 
                                  this frame was mapped. Can update this value by 
                                  calling get_current_timestamp() */
    pcb_t *process;             /* A pointer to the owning process's PCB */
    vpn_t vpn;                  /* The VPN mapped by the process using this frame. */
} fte_t;

/* A convenient global reference to the frame table, which you will
   set up in paging.c */
extern fte_t *frame_table;      /* The frame table */

/*
 * Paging functions.
 *
 * These will be completed by you in the corresponding files, paging.c,
 * page_fault.c, and page_replacement.c.
 */
void system_init(void);

void proc_init(pcb_t *proc);
void context_switch(pcb_t *proc);
void proc_cleanup(pcb_t *proc);

uint8_t mem_access(vaddr_t address, char write, uint8_t data);

pfn_t free_frame(void);
void page_fault(vaddr_t address);
