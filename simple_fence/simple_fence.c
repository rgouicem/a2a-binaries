#include <stdio.h>
#include <pthread.h>

/* #include <threads.h> */
/* #include <stdatomic.h> */

/* #include "barrier.h" */

#define LOOPS 10000000

static int X, Y;

pthread_barrier_t barrier;
/* barrier_t barrier; */

static int nr_fails, nr_tests;

/* int fn1(void *args) */
void *fn1(void *args)
{
	for (int i = 0; i < nr_tests; i++) {
		/* printf("thread 1: Loop %d barrier\n", i); */
		/* barrier_wait(&barrier); */
		pthread_barrier_wait(&barrier);

		X = 1;
		Y = 1;
	}

	return 0;
}

/* int fn2(void *args) */
void *fn2(void *args)
{
	for (int i = 0; i < nr_tests; i++) {
		/* printf("thread 2: Loop %d barrier\n", i); */
		/* barrier_wait(&barrier); */
		pthread_barrier_wait(&barrier);

		if (Y == 1 && X == 0)
			nr_fails++;

		X = Y = 0;
	}

	return 0;
}

int main()
{
	/* thrd_t threads[2]; */
	pthread_t threads[2];

	nr_fails = 0;
	nr_tests = LOOPS;

	/* barrier_init(&barrier, 2); */
	pthread_barrier_init(&barrier, NULL, 2);
	/* thrd_create(threads, fn1, NULL); */
	/* thrd_create(threads + 1, fn2, NULL); */
	pthread_create(threads, NULL, fn1, NULL);
	pthread_create(threads + 1, NULL, fn2, NULL);


	/* thrd_join(threads[0], NULL); */
	/* thrd_join(threads[1], NULL); */
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	printf("\n"
	       "Results:\n"
	       "Tests run: %d\n"
	       "\tFailed: %d\n"
	       "\tSuccess: %d\n",
	       nr_tests, nr_fails, nr_tests - nr_fails);

	return 0;
}
