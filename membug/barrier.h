#include <threads.h>

typedef struct barrier {
	cnd_t cond;
	mtx_t mutex;
	int count;
	int nr_waiters;
} barrier_t;

static inline int barrier_init(barrier_t *b, int nr_waiters)
{
	mtx_init(&b->mutex, mtx_plain);
	b->nr_waiters = b->count = nr_waiters;
	cnd_init(&b->cond);

	return 0;
}

static inline int barrier_wait(barrier_t *b)
{
	mtx_lock(&b->mutex);
	b->count--;

	if (!b->count) {
		b->count = b->nr_waiters;
		mtx_unlock(&b->mutex);
		cnd_broadcast(&b->cond);
	} else {
		cnd_wait(&b->cond, &b->mutex);
		mtx_unlock(&b->mutex);
	}

	return 0;
}
