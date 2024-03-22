/**
 * @file pthread.h 
 */
/* Embedded Xinu, Copyright (C) 2023.  All rights reserved. */

#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#include <stddef.h>
#include <stdarg.h>
#include <compiler.h>

typedef unsigned int pthread_t; 
typedef unsigned int pthread_mutex_t;

syscall ptcreate(pthread_t *thrid, ulong attr, void *start_routine, void *args);
ulong pthread_create(pthread_t *threadid, uint attr, void *start_routine, void *args);
ulong pthread_mutex_lock(uint lock);
ulong pthread_mutex_unlock(uint lock);
syscall pthread_join(pthread_t thread, void **retval);

#define PTHREAD_MUTEX_INITIALIZER lock_create()

#endif                          /* _PTHREAD_H_ */
