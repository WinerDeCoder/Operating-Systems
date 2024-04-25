#ifndef PTHREAD_H
#include <pthread.h>
#endif

typedef struct pthread_seqlock { /* TODO: implement the structure */
   pthread_mutex_t mtx;
   pthread_cond_t cond;
   int seq;
} pthread_seqlock_t;

static inline void pthread_seqlock_init(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_init(&rw->mtx, NULL);
   pthread_cond_init(&rw->cond, NULL);
   rw->seq = 0;
}

static inline void pthread_seqlock_wrlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_lock(&rw->mtx);
   rw->seq++;
   pthread_mutex_unlock(&rw->mtx);

}

static inline void pthread_seqlock_wrunlock(pthread_seqlock_t *rw)
{

   /* TODO: ... */
   pthread_mutex_lock(&rw->mtx);
   rw->seq++;
   pthread_cond_broadcast(&rw->cond);
   pthread_mutex_unlock(&rw->mtx);



}

static inline unsigned pthread_seqlock_rdlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   int seq;
   pthread_mutex_lock(&rw->mtx);
   seq = rw->seq;
   pthread_mutex_unlock(&rw->mtx);
   pthread_mutex_lock(&rw->mtx);
   while(seq == rw->seq){
      pthread_cond_wait(&rw->cond, &rw->mtx);
   }
   pthread_mutex_unlock(&rw->mtx);
   return 1;
}

static inline unsigned pthread_seqlock_rdunlock(pthread_seqlock_t *rw)
{
   /* TODO: ... */
   pthread_mutex_lock(&rw->mtx);
   rw->seq++;
   pthread_cond_broadcast(&rw->cond);
   pthread_mutex_unlock(&rw->mtx);
   return 0;
}

