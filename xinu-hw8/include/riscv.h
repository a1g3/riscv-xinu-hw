#ifndef  _RISCV_H_
#define  _RISCV_H_

#define RISCV_MSTATUS_SUM       1L<<18
#define RISCV_MSTATUS_MEI_BIT   1<<3    /* IRQs globally disabled on all privilege levels when set to 1. */
#define RISCV_MPP_TO_S_MODE     1<<11   /* Set the previous mode to S-mode so XINU can switch to S-Mode when completed. */
#define RISCV_SPP_TO_U_MODE     1<<8    /* Set the previous mode to U-mode so XINU can switch to U-Mode when completed. */
#define RISCV_SIE_ENABLE        1<<1
#define RISCV_SIE_DISABLE       0<<1
#define RISCV_MDELEG_ALL_S_MODE 0xFFFFFFFFFFFFFFFF
#define RISCV_ENV_UMODE         1L<<8

#define RISCV_MAX_ADDR 0x80000000ull
#define RISCV_ALL_PERM 0xF

#define RISCV_ENABLE_ALL_SMODE_INTR (RISCV_SIE_SEIE | RISCV_SIE_STIE | RISCV_SIE_SSIE)
#define RISCV_SIE_SEIE 1<<9
#define RISCV_SIE_STIE 1<<5
#define RISCV_SIE_SSIE 1<<1

#define SSTATUS_S_MODE	1L<<8
#define SSTATUS_U_MODE	0x0
#define SSTATUS_PRIV_MODE_BIT	1L<<8

#define PREGS   34

#define PREG_A0 0
#define PREG_A1 1
#define PREG_A2 2
#define PREG_A3 3
#define PREG_A4 4
#define PREG_A5 5
#define PREG_A6 6
#define PREG_A7 7
#define PREG_S0 8
#define PREG_S1 9
#define PREG_S2 10
#define PREG_S3 11
#define PREG_S4 12
#define PREG_S5 13
#define PREG_S6 14
#define PREG_S7 15
#define PREG_S8 16
#define PREG_S9 17
#define PREG_S10 18
#define PREG_S11 19
#define PREG_RA 20
#define PREG_SP 21
#define PREG_PC 22

#define PREG_GP 23
#define PREG_TP 24
#define PREG_T0 25
#define PREG_T1 26
#define PREG_T2 27
#define PREG_T3 28
#define PREG_T4 29
#define PREG_T5 30
#define PREG_T6 31

#define PREG_KERNSATP 32
#define PREG_KERNSP 33

#define PROCHEAPADDR   0x50000000
#define PROCSTACKADDR   0x70000000
#define SWAPAREAADDR    0x70010000    // truncpage((MAXVIRTADDR - PAGE_SIZE))

#endif                          /* _RISCV_H_ */