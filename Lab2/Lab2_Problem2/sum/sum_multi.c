
// CPP Program to find sum of array
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
  
// size of array

  
// maximum number of threads
int sum=0;
int part = 0;
  
void* sum_array(int num_threads,int n)
{
    //sum=0;
    // Each thread computes sum of 1/4th of array
    int thread_part = part++;
    int part_open = (thread_part)*n/num_threads+1;
    int part_end = (thread_part+1)*n/num_threads;
    for (int i = part_open; i <= part_end; i++)
        sum += i;  
    if (thread_part == num_threads -1)
        printf("Sum of array is %d", sum);
        
    //
}
  
// Driver Code
int main(int argc, char *argv[])
{
    int num_thread=atoi(argv[1]);
    int n = atoi(argv[2]);
    printf("Number of threads: %d\n",num_thread);
    printf("n: %d\n",n);
    //scanf("%d", &n);
    //scanf("%d", &num_thread);
    //make int sum[num_thread] = {0};    //int sum[num_thread] = { 0 };
  
    pthread_t threads[num_thread];


    for (int i = 0; i < num_thread; i++)
        pthread_create(&threads[i], NULL, sum_array(num_thread,n), (void*)NULL);
  
    // joining 4 threads i.e. waiting for all 4 threads to complete
    for (int i = 0; i < num_thread; i++)
        pthread_join(threads[i], NULL);
  
    // adding sum of all 4 parts

    //printf("sum is %d", sum);
    //printf("o: %d", part);
    pthread_exit(0);
    return 0;
}