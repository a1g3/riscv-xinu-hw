/**
 * @file     ctxsw.s
 * @provides ctxsw
 *
 * COSC 3250 / COEN 4820 Assignment 4
 */
/* Embedded XINU, Copyright (C) 2023.  All rights reserved. */

#include <riscv.h>

.text
	.align 4
	.globl	ctxsw


/**
 * @fn void ctxsw(&oldcontext, &newcontext)
 *
 * Switch context (values in registers) to another process, saving the
 * current processes information. This function will not return as normally
 * thought as it will load in the program counter for a different process and
 * jump to that location and begin executing code.
 *
 * @param  &oldcontext address of outgoing process context save area
 * @param  &newcontext address of incoming process context save area
 * @return special case -- see above
 */
	.func ctxsw
ctxsw:

// TODO: Save process state, including at least the 
//	callee-save ("non-volatile") registers.
// TODO: Switch from old process stack to new process stack.
// TODO: Restore process state, including at least the
//	callee-save ("non-volatile") registers.
//	These call and restore segments must match the register data
//	layout you choose in create().
// TODO: Jump to next function.
//	Note: there are two important values at play here --
//	the address of the process's function that we want to end up in
//	once we leave this ctxsw(), and the value we want to have in the
//	return address register.  Those are almost always the same value, except
//	for the very first time we ctxsw() to a new process, when they
//	are different.  See create() for more details.

// Note: This ret line immediately returns from whence we came.  This
//	is here as a placeholder so that you don't crash your O/S when
//	you call ctxsw() before it is complete.  But, this line of code
//	is not actually a part of a completed solution.
	ret

// ASSIGNMENT 5 TODO:
// Note: the following code is for the next assignment.  DO NOT uncomment it until you believe your trap handler is working in assignment
// Determine which mode we privilege mode the process should be in
//	ld t0, (**REGISTER THAT HOLDS NEW CONTEXT PROGRAM COUNTER**)
//	beq t0, ra, switch
//	li t4, SSTATUS_S_MODE
//	csrc sstatus, t4
//	csrw sepc, t0
//
//	sret
//switch:
//	ret

	.end ctxsw
