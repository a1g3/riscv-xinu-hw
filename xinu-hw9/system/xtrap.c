#include <xinu.h>

// Found in 3.1.15 Machine Cause Register in the RISC-V Privileged documentation
char *trap_names[] = {
    "Instruction address misaligned",
    "Instruction access fault",
    "Illegal instruction",
    "Breakpoint",
    "Load address misaligned",
    "Load access fault",
    "Store/AMO address misaligned",
    "Store/AMO access fault",
    "Environment call from U-mode",
    "Environment call from S-mode",
    "Reserved",
    "Environment call from M-mode",
    "Instruction page fault",
    "Load page fault",
    "Reserved", 
    "Store/AMO page fault"
};

void xtrap(ulong *frame, ulong cause, ulong address, ulong *pc)
{
    /* If not an interrupt or syscall, fall through to generic exception handler */
    kprintf("\r\n\r\nXINU Exception [%s]\r\n", trap_names[cause]);
    kprintf("Faulting code: 0x%016lX\r\n", pc);

    if (address != 0){
        kprintf("Faulting address: 0x%016lX\r\n", address);
    }

    kprintf("[0x%016lX]  t4:0x%016lX   t5:0x%016lX  t6:0x%016lX\r\n",
            frame + PREG_T4,
            frame[PREG_T4], frame[PREG_T5], frame[PREG_T6]); 
    kprintf("[0x%016lX]  s9:0x%016lX   s10:0x%016lX  s11:0x%016lX  t3:0x%016lX\r\n",
            frame + PREG_S9,
            frame[PREG_S9], frame[PREG_S10], frame[PREG_S11], frame[PREG_T3]); 
    kprintf("[0x%016lX]  s5:0x%016lX   s6:0x%016lX  s7:0x%016lX  s8:0x%016lX\r\n",
            frame + PREG_S5,
            frame[PREG_S5], frame[PREG_S6], frame[PREG_S7], frame[PREG_S8]); 
    kprintf("[0x%016lX]  a7:0x%016lX   s2:0x%016lX  s3:0x%016lX  s4:0x%016lX\r\n",
            frame + PREG_A7,
            frame[PREG_A7], frame[PREG_S2], frame[PREG_S3], frame[PREG_S4]); 
    kprintf("[0x%016lX]  a3:0x%016lX   a4:0x%016lX  a5:0x%016lX  a6:0x%016lX\r\n",
            frame + PREG_A3,
            frame[PREG_A3], frame[PREG_A4], frame[PREG_A5], frame[PREG_A6]);            
    kprintf("[0x%016lX]  s1:0x%016lX   a0:0x%016lX  a1:0x%016lX  a2:0x%016lX\r\n",
            frame + PREG_S1,
            frame[PREG_S1], frame[PREG_A0], frame[PREG_A1], frame[PREG_A2]);
    kprintf("[0x%016lX]  t0:0x%016lX   t2:0x%016lX   t2:0x%016lX   s0:0x%016lX\r\n",
            frame + PREG_T0,
            frame[PREG_T0], frame[PREG_T1], frame[PREG_T2], frame[PREG_S0]);
    kprintf("[0x%016lX]  ra:0x%016lX   sp:0x%016lX   gp:0x%016lX   tp:0x%016lX\r\n",
            frame + PREG_RA,
            frame[PREG_RA], frame[PREG_SP], frame[PREG_GP], frame[PREG_TP]);
    while (1)
        ;                       /* forever */
}