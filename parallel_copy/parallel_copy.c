#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MULT 1024

int *buf, *cpy;
unsigned long buf_size = 1024;
int nr_threads = 2;

void *copy(void *arg)
{
	long id = (long) arg;
	int my_size = buf_size / nr_threads;
	int *start = (void *)buf + my_size * id;

	for (unsigned long i = 0; i < my_size / sizeof(int); i++) {
		int tmp = start[i];

		cpy[id * my_size / sizeof(int) + i] = tmp * 9 + 42;
	}

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t *tids;

	if (argc == 3) {
		nr_threads = atoi(argv[1]);
		buf_size = atoi(argv[2]);
	} else {
		return -1;
	}

	// allocate + init buffer randomly
	buf_size *= MULT;
	buf = malloc(buf_size);
	for (unsigned long i = 0; i < buf_size / sizeof(int); i++)
		buf[i] = rand();
	cpy = malloc(buf_size);
	memset(cpy, 0, buf_size);

	// create threads
	tids = malloc(nr_threads * sizeof(pthread_t));
	for (long i = 0; i < nr_threads; i++) {
		pthread_create(tids + i, NULL, copy, (void *)i);
	}

	// join threads
	for (int i = 0; i < nr_threads; i++)
		pthread_join(tids[i], NULL);

	free(buf);
	free(tids);
	
	return 0;
}
