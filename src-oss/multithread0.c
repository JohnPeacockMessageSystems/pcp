/*
 * Copyright (c) 2011 Ken McDonell.  All Rights Reserved.
 *
 * exercise __pmMultiThreaded()
 */

#include <stdio.h>
#include <stdlib.h>
#include <pcp/pmapi.h>
#include <pcp/impl.h>
#include <pthread.h>

static void *
func(void *arg)
{
    if (__pmMultiThreaded())
	printf("func: is multithreaded\n");
    else
	printf("func: is NOT multithreaded\n");
    pthread_exit(NULL);
}

int
main()
{
    pthread_t	tid1;
    pthread_t	tid2;
    int		sts;
    char	*msg;

    if (__pmMultiThreaded())
	printf("main0: is multithreaded\n");
    else
	printf("main0: is NOT multithreaded\n");

    sts = pthread_create(&tid1, NULL, func, NULL);
    if (sts != 0) {
	printf("thread_create: tid1: sts=%d\n", sts);
	exit(1);
    }

    if (__pmMultiThreaded())
	printf("main1: is multithreaded\n");
    else
	printf("main1: is NOT multithreaded\n");

    sts = pthread_create(&tid2, NULL, func, NULL);
    if (sts != 0) {
	printf("thread_create: tid2: sts=%d\n", sts);
	exit(1);
    }

    if (__pmMultiThreaded())
	printf("main2: is multithreaded\n");
    else
	printf("main2: is NOT multithreaded\n");

    pthread_join(tid1, (void *)&msg);
    if (msg != NULL) printf("tid1: %s\n", msg);
    pthread_join(tid2, (void *)&msg); 
    if (msg != NULL) printf("tid2: %s\n", msg);

    exit(0);
}
