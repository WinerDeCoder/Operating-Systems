#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_ITEMS 3
#define THREADS 1 // 1 producer and 1 consumer
#define LOOPS 2 * MAX_ITEMS // variable



// Initiate shared buffer
int buffer[MAX_ITEMS];
int fill = 0;
int use = 0;

/*TODO: Fill in the synchronization stuff */
//create semaphore
sem_t sem;
sem_t sem2;
void put(int value); // put data into buffer
int get(); // get data from buffer

void * producer(void * arg) {
  int i;
  int tid = (int) arg;
  for (i = 0; i < LOOPS; i++) {
    /*TODO: Fill in the synchronization stuff */
    sem_wait(&sem2);
    put(i); // line P2
    
    printf("Producer %d put data %d\n", tid, i);
    //put(i);
    
    sleep(1);
    sem_post(&sem2);
    /*TODO: Fill in the synchronization stuff */
  }
  pthread_exit(NULL);
}

void * consumer(void * arg) {
  int i,tmp = 0;
  int tid = (int) arg;
  while (tmp != -1) {
    /*TODO: Fill in the synchronization stuff */
    
    sem_wait(&sem);
    tmp = get(); // line C2
    
    printf("Consumer %d get data %d\n", tid, tmp);
    //printf("i: %d", i);
    sleep(1);   
 
    if(tmp ==LOOPS -1){
      break;
    }
    sem_post(&sem);      
    
    
    
    //signal(&sem);
    
    
    /*TODO: Fill in the synchronization stuff */
  }
  pthread_exit(NULL);
}

int main(int argc, char ** argv) {
  
  int i, j;
  int tid[THREADS];
  pthread_t producers[THREADS];
  pthread_t consumers[THREADS];

  /*TODO: Fill in the synchronization stuff */
  sem_init(&sem, 1,2);
  sem_init(&sem2, 1,2);

  for (i = 0; i < THREADS; i++) {
    tid[i] = i;
    // Create producer thread
    pthread_create( & producers[i], NULL, producer, (void * ) tid[i]);

    // Create consumer thread
    pthread_create( & consumers[i], NULL, consumer, (void * ) tid[i]);
  }

  for (i = 0; i < THREADS; i++) {
    pthread_join(producers[i], NULL);
    pthread_join(consumers[i], NULL);
  }

  sem_destroy(&sem);
  sem_destroy(&sem2);
  /*TODO: Fill in the synchronization stuff */

  return 0;
}

void put(int value) {
  buffer[fill] = value; // line f1
  fill = (fill + 1) % MAX_ITEMS; // line f2
}

int get() {
  int tmp = buffer[use]; // line g1
  use = (use + 1) % MAX_ITEMS; // line g2
  return tmp;
}