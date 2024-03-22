/**
 * @file interrupt.S
 */
/* Embedded Xinu, Copyright (C) 2013.  All rights reserved. */

#include <riscv.h>  /* Needed for ARM_MODE_SYS definition.  */

.text
    .align 4
.globl criticalerr

/**
 * Entry point for Xinu's interrupt handler (RISC-V version). 
 */
criticalerr:
	.func criticalerr
    csrw mscratch, sp

    li sp, 0x52000000
    addi sp, sp, PREGS*-8

    sd t0, PREG_T0*8(sp)
    csrr t0, mscratch
    sd t0, PREG_SP*8(sp)

    sd ra, PREG_RA*8(sp)
    sd gp, PREG_GP*8(sp)
    sd tp, PREG_TP*8(sp)
    sd t1, PREG_T1*8(sp)
    sd t2, PREG_T2*8(sp)
    sd s0, PREG_S0*8(sp)
    sd s1, PREG_S1*8(sp)
    sd a0, PREG_A0*8(sp)
    sd a1, PREG_A1*8(sp)
    sd a2, PREG_A2*8(sp)
    sd a3, PREG_A3*8(sp)
    sd a4, PREG_A4*8(sp)
    sd a5, PREG_A5*8(sp)
    sd a6, PREG_A6*8(sp)
    sd a7, PREG_A7*8(sp)
    sd s2, PREG_S2*8(sp)
    sd s3, PREG_S3*8(sp)
    sd s4, PREG_S4*8(sp)
    sd s5, PREG_S5*8(sp)
    sd s6, PREG_S6*8(sp)
    sd s7, PREG_S7*8(sp)
    sd s8, PREG_S8*8(sp)
    sd s9, PREG_S9*8(sp)
    sd s10, PREG_S10*8(sp)
    sd s11, PREG_S11*8(sp)
    sd t3, PREG_T3*8(sp)
    sd t4, PREG_T4*8(sp)
    sd t5, PREG_T5*8(sp)
    sd t6, PREG_T6*8(sp)

    csrr a1, mcause
    slli a1, a1, 1
    srli a1, a1, 1

    mv a0, sp
    csrr a1, mcause
    csrr a2, mtval
    csrr a3, mepc
    j xtrap
    .endfunc