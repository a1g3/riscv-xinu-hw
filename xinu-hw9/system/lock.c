/**
 * @file spinlock.c
 * @provides lock_create, lock_free, lock_acquire, lock_release.
 *
 */
/* Embedded Xinu, Copyright (C) 2008. All rights reserved. */

#include <xinu.h>

struct lockent locktab[NLOCK];  /* spinlock table */

/* Assembly helper functions in spinlock_util.S */
extern void _lock_acquire(volatile unsigned long *);
extern void _lock_release(volatile unsigned long *);

static spinlock_t lock_alloc(void);

/**
 * Create and initialize a spinlock, returning its ID.
 * @return new lock ID on success, SYSERR on failure
 */
spinlock_t lock_create()
{
    spinlock_t lock;

    lock = lock_alloc();
    if (SYSERR == lock)
    {
        return SYSERR;
    }

    locktab[lock].lock = 1;
    locktab[lock].lock = SPINLOCK_UNLOCKED;
    return lock;
}

/**
 * Deallocate a lock.
 * Reset the lock entry, and deallocate 
 * the entry from the global lock table.
 * NOTE: This function can potentially 
 * 		 not be thread safe. Undefined behavior
 * 		 can occur if more than one thread
 * 		 attempts to free a lock.
 *       
 * @param lock	target lock
 * @return OK on success, SYSERR on failure
 */
syscall lock_free(spinlock_t lock)
{
    if (isbadlock(lock))
        return SYSERR;

    locktab[lock].state = SPINLOCK_FREE;

    return OK;
}

/**
 * Acquire a lock.
 * @param lock	target lock
 * @return OK on success, SYSERR on failure
 */
syscall lock_acquire(spinlock_t lock)
{
    if (isbadlock(lock))
    {
        return SYSERR;
    }

    _lock_acquire(&(locktab[lock].lock));
    disable();
    locktab[lock].core = 1;

    return OK;
}

/**
 * release a lock
 * @param lock	target lock
 * @return OK on success, SYSERR on failure
 */
syscall lock_release(spinlock_t lock)
{
    if (isbadlock(lock))
        return SYSERR;

    locktab[lock].core = -1;

    _lock_release(&(locktab[lock].lock));
    enable();

    return OK;
}

/**
 * Allocate an unused lock and return its ID.
 * Scan the global lock table for a free entry, mark the entry
 * used, and return the new lock.
 * @return available lock ID on success, SYSERR on failure
 */
static spinlock_t lock_alloc(void)
{
    int i;

    /* check all entries */
    for (i = 0; i < NLOCK; i++)
    {
        if (_atomic_compareAndSwapWeak
            (&(locktab[i].state), SPINLOCK_FREE, SPINLOCK_USED))
            return i;
    }
    return SYSERR;
};