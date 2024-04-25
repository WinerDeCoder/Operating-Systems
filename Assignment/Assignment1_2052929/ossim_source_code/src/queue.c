#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */
	if (q->size < MAX_QUEUE_SIZE)
	{
		q->proc[q->size] = proc;
		q->size += 1;
		
	}
		
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	 if (q->size == 0) {
		return NULL;
	}
	 struct pcb_t * temp ;
	 temp = q->proc[0];
	 move_up(q);
	 
	  q->size -= 1;
	return temp;
}

void move_up(struct queue_t * q)
{
	for (int i = 0 ; i <= q->size -2 ; ++i)
	{
		q->proc[i] = q->proc[i+1];	
	}
	
}

int check_empty(struct queue_t * q)
{
	return q->size;
}
