#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>

#define MULT 1024

#define ts_to_ns(ts) (ts.tv_sec * 1E9 + ts.tv_nsec)

int *buf, *cpy;
unsigned long buf_size = 1024;
int nr_threads = 2;

int cmp(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void *fn(void *arg)
{
	long id = (long) arg;
	int my_size = buf_size / nr_threads;
	int *start = (void *)buf + my_size * id;

	qsort(start, my_size / sizeof(int), sizeof(int), cmp);

	return NULL;
}

/* void *fn(void *arg) */
/* { */
/* 	long id = (long) arg; */
/* 	int my_size = buf_size / nr_threads; */
/* 	int *start = (void *)buf + my_size * id; */

/* 	for (unsigned long i = 0; i < my_size / sizeof(int); i++) { */
/* 		int tmp = start[i]; */

/* 		cpy[id * my_size / sizeof(int) + i] = tmp * 9 + 42; */
/* 	} */

/* 	return NULL; */
/* } */

int main(int argc, char **argv)
{
	pthread_t *tids;
	struct timespec ts;
	uint64_t start_mono, end_mono, start_multi, end_multi;

	if (argc == 3) {
		nr_threads = atoi(argv[1]);
		buf_size = atoi(argv[2]);
	} else {
		return -1;
	}

	clock_gettime(CLOCK_MONOTONIC, &ts);
	start_mono = ts_to_ns(ts);
	// allocate + init buffer randomly
	buf_size *= MULT;
	buf = malloc(buf_size);
	for (unsigned long i = 0; i < buf_size / sizeof(int); i++)
		buf[i] = rand();
	cpy = malloc(buf_size);
	memset(cpy, 0, buf_size);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	end_mono = ts_to_ns(ts);
	printf("Single thread duration (allocation + touch): %lu ns\n",
	       end_mono - start_mono);

	clock_gettime(CLOCK_MONOTONIC, &ts);
	start_multi = ts_to_ns(ts);
	// create threads
	tids = malloc(nr_threads * sizeof(pthread_t));
	for (long i = 0; i < nr_threads; i++) {
		pthread_create(tids + i, NULL, fn, (void *)i);
	}

	// join threads
	for (int i = 0; i < nr_threads; i++)
		pthread_join(tids[i], NULL);

	clock_gettime(CLOCK_MONOTONIC, &ts);
	end_multi = ts_to_ns(ts);
	printf("Multi thread duration (copy): %lu ns\n",
	       end_multi - start_multi);

	free(buf);
	free(tids);
	
	return 0;
}
