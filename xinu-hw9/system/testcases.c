/**
 * @file testcases.c
 * @provides testcases
 *
 *
 * Modified by:	
 *
 * TA-BOT:MAILTO 
 *
 */
/* Embedded XINU, Copyright (C) 2023.  All rights reserved. */

#include <xinu.h>

#define MAX 10000
#define THRD_COUNT 4

/* This struct lets us pass three items to each thread */
typedef struct
{
  int *array;
  int length;
  long int *answer;
  pthread_mutex_t lock;
} myarg_t;

/* Each thread will sum up its part of the array */
void *mythread(void *arg)
{
  /* Cast the generic args to be our myarg_t struct */
  myarg_t *args = (myarg_t *)arg;
  
  int i = 0;

  //kprintf("Adding %d to %d\r\n", args->array[0], args->array[args->length - 1]);
  for (i = 0; i < args->length; i++)
    {
	  // TODO: Uncomment these lines for locking
      //pthread_mutex_lock(args->lock);
      *(args->answer) += args->array[i];
      //pthread_mutex_unlock(args->lock);
    }
  return NULL;
}

int test_main(void) {
	int *array = NULL;               /* Array of numbers to add up        */
	long int answer = 0;             /* Answers from each thread          */
	pthread_t threads[THRD_COUNT];   /* PThread objects                   */
	myarg_t args[THRD_COUNT];        /* Argument struct, one per thread   */
	int i = 0;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	array = (int *)malloc(MAX * sizeof(int));
	if (NULL == array) return -1;

	/* Initialize data from 1 to MAX  */
	for (i = 0; i < MAX; i++) { array[i] = i + 1; }

	/* Initialize Per-thread argument structs */
	for (i = 0; i < THRD_COUNT; i++)
		{
		/* Each thread gets its own portion of the array */
		args[i].array = array + i * (MAX / THRD_COUNT);
		args[i].length = MAX / THRD_COUNT;
		/* Each thread gets its own answer spot */
		args[i].answer = &answer;
		args[i].lock = lock;
		}

	/* Create all of the worker threads */
	for (i = 0; i < THRD_COUNT; i++)
		{
		threads[i] = pthread_create(NULL, NULL, mythread, args + i);
		//kprintf("Spawned thread %d\r\n", i);
		}

	kprintf("Joining threads!\r\n");
	/* Use join() to wait for each thread to complete its work */
	for (i = 0; i < THRD_COUNT; i++)
		{
		pthread_join(threads[i], NULL);
		}

	kprintf("Final answer is %d\r\n", answer);
	
	return 0;
}

/**
 * testcases - called after initialization completes to test things.
 */
void testcases(void)
{
	uchar c;

	kprintf("===TEST BEGIN===\r\n");

	// TODO: Test your operating system!

	c = kgetc();
	switch (c)
	{
		case '0':
			// TODO: Get this test case working just like in class
			ready(create((void *)test_main, INITSTK, PRIORITY_HIGH, "TEST PROC", 0), RESCHED_YES);
			break;
		// TODO: WRITE MORE TEST CASES!
		default:
			break;
	}

	kprintf("\r\n===TEST END===\r\n");
	return;
}
