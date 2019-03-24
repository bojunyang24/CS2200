#include "paging.h"
#include "stats.h"

/* The stats. See the definition in stats.h. */
stats_t stats;

/*  --------------------------------- PROBLEM 10 --------------------------------------
    Checkout PDF section 10 for this problem

    Calculate any remaining statistics to print out.

    You will need to include code to increment many of these stats in
    the functions you have written for other parts of the project.

    Use this function to calculate any remaining stats, such as the
    average access time (AAT).

    You may find the #defines in the stats.h file useful.
    -----------------------------------------------------------------------------------
*/
void compute_stats() {
    // stats.accesses = stats.writes + stats.reads;
    uint64_t readTime = stats.reads * MEMORY_READ_TIME;
    uint64_t writeTime = stats.writes * MEMORY_READ_TIME;
    uint64_t pageFaultTime = stats.page_faults * DISK_PAGE_READ_TIME;
    uint64_t writebackTime = stats.writebacks * DISK_PAGE_WRITE_TIME;
    stats.aat = (readTime + writeTime + pageFaultTime + writebackTime) / ((double) stats.accesses);
}
