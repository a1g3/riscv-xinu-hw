#include <xinu.h>

static ulong *pgTraverseAndCreate(pgtbl pagetable, ulong virtualaddr, int attr);

/**
 * Maps a page to a specific virtual address
 * @param pagetable     the base pagetable
 * @param page          the page that will be stored at the virtual address
 * @param virtualaddr   the virtual address at which the page will reside
 * @param attr          any attributes to set on the page table entry
 * @return              OK if successful, otherwise a SYSERR
 */
syscall mapPage(pgtbl pagetable, page pg, ulong virtualaddr, int attr)
{
    ulong addr;

    addr = (ulong)truncpage(virtualaddr);

    if (pgTraverseAndCreate(pagetable, addr, attr) == (ulong *)SYSERR)
    {
        return SYSERR;
    }

    return OK;
}

/**
 * Maps a given virtual address range to a corresponding physical address range.
 * @param pagetable    the base pagetable
 * @param virtualaddr  the start of the virtual address range. This will be truncated to the nearest page boundry.
 * @param physicaladdr the start of the physical address range
 * @param length       the length of the range to map
 * @param attr         any attributes to set on the page table entry
 * @return             OK if successful, otherwise a SYSERR
 */
syscall mapAddress(pgtbl pagetable, ulong virtualaddr, ulong physicaladdr,
               ulong length, int attr)
{
    ulong addr, end;
    ulong nlength;


    if (length == 0)
    {
        return SYSERR;
    }

    // Round the length to the nearest page size
    nlength = roundpage(length);
    addr = (ulong)truncpage(virtualaddr);
    end = addr + nlength;

    // Loop over the entire range
    for (; addr < end; addr += PAGE_SIZE, physicaladdr += PAGE_SIZE)
    {
        // Create a page table entry if one doesn't exist. Otherwise, get the existing page table entry.
        if (pgTraverseAndCreate(pagetable, addr, attr) == (ulong *)SYSERR)
        {
            return SYSERR;
        }
    }

    return OK;
}

/**
 * Starting at the base pagetable, tranverse the hierarchical page table structure for the virtual address.  Create pages along the way if they don't exist.
 * @param pagetable    the base pagetable
 * @param virtualaddr  the virtual address to find the it's corresponding page table entry.
 * @param attr	       the attributes to set on the leaf page
 * @return             OK
 */
static ulong *pgTraverseAndCreate(pgtbl pagetable, ulong virtualaddr, int attr)
{
    /**
    * TODO:
    * For each level in the page table, get the page table entry by masking and shifting the bits in the virtualaddr depending on the level
    * If the valid bit is set, use that pagetable for the next level
    * Otherwise create the page by calling pgalloc().  Make sure to setup the page table entry accordingly. Call sfence_vma once finished to flush TLB
    * Once you've tranversed all three levels, set the attributes (attr) for the leaf page (don't forget to set the valid bit!)
    */
    return (ulong *)OK;
}

