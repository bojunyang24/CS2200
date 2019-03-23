#pragma once

#include "paging.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/*  --------------------------------- PROBLEM 1 --------------------------------------
    Checkout PDF Section 2 For this Problem

    Split the virtual address into VPN and offset.
    These macros will be used whenever you get a memory address from the CPU and need
    to translate it.

    HINT: Examine the global defines in pagesim.h, which will be
    necessary in implementing these functions.

    HINT: While these values will be powers of two, allowing you to use bit-wise
    arithmetic, consider using modulus division and integer division for
    an elegant solution.
    -----------------------------------------------------------------------------------
 */

/* Get the virtual page number from a virtual address. */
static inline vpn_t vaddr_vpn(vaddr_t addr) {
    return 0;                   /* FIXME */
}

/* Get the offset into the page from a virtual address. */
static inline uint16_t vaddr_offset(vaddr_t addr) {
    return 0;                   /* FIXME */
}

#pragma GCC diagnostic pop
