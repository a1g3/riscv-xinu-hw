/**
 * @file memory.h
 * Definitions for kernel memory allocator and maintenance.
 *
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <stddef.h>
//#include <spinlock.h>

/* roundmb - round address up to size of memblock  */
#define roundmb(x)  (void *)( (15 + (ulong)(x)) & ~0xF )
/* truncmb - truncate address down to size of memblock */
#define truncmb(x)  (void *)( ((ulong)(x)) & ~0xF )

/**
 * Structure for a block of memory.
 */
typedef struct memblock
{
    struct memblock *next;      /* pointer to next memory block       */
    ulong length;               /* size of memory block (with struct) */
} memblk;

/**
 * Structure for the head of the memory list.
 */
typedef struct memhead
{
    struct memblock *head;      /* pointer to first memory block      */
    ulong length;               /* non-constant; current size of list */
    ulong base;                 /* beginning address of free list     */
    ulong bound;                /* fixed value; total size of list    */
} memhead;

/* Other memory data */

extern void *_end;              /* linker provides end of image       */
extern void *_bss;              /* linker provides start of bss       */
extern void *_datas;            /* linker provides start of data       */
extern void *memheap;           /* bottom of heap                     */
extern void *_ctxsws;           /* start of ctxsw                     */
extern void *_ctxswe;           /* end of ctxsw                       */
extern void *_interrupts;       /* start of ctxsw                     */
extern void *_interrupte;       /* end of ctxsw                       */
extern ulong _kernpgtbl;

/* Memory function prototypes */
void *getmem(ulong nbytes);
syscall freemem(void *pmem, ulong nbytes);

#endif                          /* _MEMORY_H_ */
