/**
 * @file     clkinit.c
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <xinu.h>

/** @ingroup timer
 *
 * Number of timer interrupts that have occurred since ::clktime was
 * incremented.  When ::clkticks reaches ::CLKTICKS_PER_SEC, ::clktime is
 * incremented again and ::clkticks is reset to 0.
 */
volatile ulong clkticks;

/** @ingroup timer
 * Number of seconds that have elapsed since the system booted.  */
volatile ulong clktime;

#if PREEMPT
volatile ulong preempt;
#endif

#if AGING
volatile ulong promote_medium;
volatile ulong promote_low;
#endif

/**
 * @ingroup timer
 *
 * Initialize the clock and sleep queue.  This function is called at startup.
 */
void clkinit(void)
{
    volatile struct timer *t = (volatile struct timer*)0x02050000;

#if PREEMPT
    preempt = QUANTUM;
#endif

#if AGING
    promote_medium = QUANTUM;
    promote_low = QUANTUM;
#endif

    clkticks = 0;
    clktime = 0;

    // Enable TIMER0
    t->enable = 1;

	// Seting TIMER0's initial value to 500
    t->timer_init_val = 100;

    t->control = (uint)( (1 << 7) | (1 << 0) );

    // PLIC interrupt priority for TIMER0
    uint *reg = (uint *)(PLIC_BASE + (0x12C));
    *reg = (uint)31;

	// Enable the TIMER0 interrupt for supervisor mode
    uint *timer_enable_reg = (uint *)(PLIC_BASE + 0x2080 + 0x8);
    *timer_enable_reg |= (1 << 11);

    kprintf("Time base %dHz, Clock ticks at %dHz\r\n",
            platform.clkfreq, CLKTICKS_PER_SEC);

    /* register clock interrupt */
    interruptVector[IRQ_TIMER] = clkhandler;
}
