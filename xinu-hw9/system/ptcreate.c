/**
 * @file ptcreate.c
 * @provides ptcreate
 *
 * COSC 3250 Assignment 9
 */
/* Embedded XINU, Copyright (C) 2023.  All rights reserved. */

#include <xinu.h>

static pid_typ newpid(void);
void userret(void);

/**
 * Create a new thread to start running a function.
 * @param thread            UNUSED IN XINU! In pthreads, this would be where the threadid is placed
 * @param attr              UNUSED IN XINU! In pthreads, this would be where any thread attributes are specified
 * @param start_routine     address of function that will begin in new process
 * @param args              a pointer to the arguments
 * @return the new thread id
 */
syscall ptcreate(pthread_t *thread, ulong attr, void *start_routine, void *args)
{
    ulong *saddr;                     /* stack address                */
    ulong pid;                        /* stores new process id        */
    pcb *parentppcb;                  /* pointer to parent proc control blk  */
    pcb *childppcb;                   /* pointer to parent proc control blk  */
	ulong child_vaddr_sbase;
	ulong child_vaddr_swapbase;

    parentppcb = &proctab[currpid];
    pid = newpid();

    /* a little error checking      */
    if (SYSERR == pid)
    {
        return SYSERR;
    }

    numproc++;
    childppcb = &proctab[pid];

    /*
    * TODO:
    * 1) Setup the child thread's PCB
    *   a) The child thread should inherit its name, priority, and pagetable from its parent
    *   b) The child thread should enjoin itself on the parent's queue
    * 2) Setup child thread's stack
    *   a) Calculate the child thread's virtual stack address relative to its PID
    *   b) Map the child thread's virtual stack address
    * 3) Setup child thread's registers (similar to create.c)
    * 4) Setup child thread's swaparea 
    *   a) Calculate the child thread's virtual swap area address relative to its PID
    *   b) Map the child thread's virtual swap area address
    * 5) Setup the child thread's kernel swaparea and kernel stack pointer (see create.c)
    * 6) Ready the child thread. Do no resched to it. 
    */
	
    return pid;
}

/**
 * Obtain a new (free) process id.
 * @return a free process id, SYSERR if all ids are used
 */
static pid_typ newpid(void)
{
    pid_typ pid;                /* process id to return     */
    static pid_typ nextpid = 0;

    for (pid = 0; pid < NPROC; pid++)
    {                           /* check all NPROC slots    */
        nextpid = (nextpid + 1) % NPROC;
        if (PRFREE == proctab[nextpid].state)
        {
            return nextpid;
        }
    }
    return SYSERR;
}
