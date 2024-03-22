/**
 * @file interrupt.S
 */
/* Embedded Xinu, Copyright (C) 2013.  All rights reserved. */

#include <riscv.h>  /* Needed for ARM_MODE_SYS definition.  */

.section .interruptsec
    .align 4
.globl interrupt

/**
 * Entry point for Xinu's interrupt handler (RISC-V version). 
 */
interrupt:
	.func interrupt
    csrw sscratch, a0

    li a0, SWAPAREAADDR

    sd t0, PREG_T0*8(a0)
    mv t0, a0
    csrr a0, sscratch

    sd sp, PREG_SP*8(t0)
    sd ra, PREG_RA*8(t0)
    sd gp, PREG_GP*8(t0)
    sd tp, PREG_TP*8(t0)
    sd t1, PREG_T1*8(t0)
    sd t2, PREG_T2*8(t0)
    sd s0, PREG_S0*8(t0)
    sd s1, PREG_S1*8(t0)
    sd a0, PREG_A0*8(t0)
    sd a1, PREG_A1*8(t0)
    sd a2, PREG_A2*8(t0)
    sd a3, PREG_A3*8(t0)
    sd a4, PREG_A4*8(t0)
    sd a5, PREG_A5*8(t0)
    sd a6, PREG_A6*8(t0)
    sd a7, PREG_A7*8(t0)
    sd s2, PREG_S2*8(t0)
    sd s3, PREG_S3*8(t0)
    sd s4, PREG_S4*8(t0)
    sd s5, PREG_S5*8(t0)
    sd s6, PREG_S6*8(t0)
    sd s7, PREG_S7*8(t0)
    sd s8, PREG_S8*8(t0)
    sd s9, PREG_S9*8(t0)
    sd s10, PREG_S10*8(t0)
    sd s11, PREG_S11*8(t0)
    sd t3, PREG_T3*8(t0)
    sd t4, PREG_T4*8(t0)
    sd t5, PREG_T5*8(t0)
    sd t6, PREG_T6*8(t0)  

    // Load kernel page table
	ld a1, PREG_KERNSATP*8(t0)
    ld sp, PREG_KERNSP*8(t0)

    sfence.vma zero, zero
	csrw satp, a1
	sfence.vma zero, zero

    csrr a0, scause 
    csrr a1, stval
    csrr a2, sepc
    call dispatch

    sfence.vma zero, zero
    mv a1, a0
	csrw satp, a1
	sfence.vma zero, zero

    li a0, SWAPAREAADDR
    ld t0, PREG_T0*8(a0)
    csrw sscratch, t0
    mv t0, a0

    ld sp, PREG_SP*8(t0)
    ld ra, PREG_RA*8(t0)
    ld gp, PREG_GP*8(t0)
    ld tp, PREG_TP*8(t0)
    ld t1, PREG_T1*8(t0)
    ld t2, PREG_T2*8(t0)
    ld s0, PREG_S0*8(t0)
    ld s1, PREG_S1*8(t0)
    ld a0, PREG_A0*8(t0)
    ld a1, PREG_A1*8(t0)
    ld a2, PREG_A2*8(t0)
    ld a3, PREG_A3*8(t0)
    ld a4, PREG_A4*8(t0)
    ld a5, PREG_A5*8(t0)
    ld a6, PREG_A6*8(t0)
    ld a7, PREG_A7*8(t0)
    ld s2, PREG_S2*8(t0)
    ld s3, PREG_S3*8(t0)
    ld s4, PREG_S4*8(t0)
    ld s5, PREG_S5*8(t0)
    ld s6, PREG_S6*8(t0)
    ld s7, PREG_S7*8(t0)
    ld s8, PREG_S8*8(t0)
    ld s9, PREG_S9*8(t0)
    ld s10, PREG_S10*8(t0)
    ld s11, PREG_S11*8(t0)
    ld t3, PREG_T3*8(t0)
    ld t4, PREG_T4*8(t0)
    ld t5, PREG_T5*8(t0)
    ld t6, PREG_T6*8(t0)

    csrr t0, sscratch

    sret

.endfunc