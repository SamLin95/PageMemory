#include <stdlib.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */
pfn_t get_free_frame(void) {
   int i;
   int idx;

   /* See if there are any free frames */
   for (i = 0; i < CPU_NUM_FRAMES; i++)
      if (rlt[i].pcb == NULL)
         return i;

   /* FIX ME : Problem 5 */
   /* IMPLEMENT A CLOCK SWEEP ALGORITHM HERE */
   /* Note: Think of what kinds of frames can you return before you decide
      to evit one of the pages using the clock sweep and return that frame */
      pte_t* pagetable;
      for (i = 0; i < CPU_NUM_FRAMES;i++) {
         pagetable = rlt[i].pcb -> pagetable;
         if (!pagetable[rlt[i].vpn].valid) {
            pagetable[rlt[i].vpn].valid = 1;
            return pagetable[rlt[i].vpn].pfn;
         }
      }



      for (i = 0; i <= CPU_NUM_FRAMES;i++) {
         idx = i % CPU_NUM_FRAMES;
         pagetable = rlt[idx].pcb -> pagetable;
         if (!pagetable[rlt[idx].vpn].used) {
            pagetable[rlt[idx].vpn].used = 1;
            return pagetable[rlt[idx].vpn].pfn;
         }
         pagetable[rlt[idx].vpn].used = 0; 
      }

   /* If all else fails, return a random frame */
   return rand() % CPU_NUM_FRAMES;
}
