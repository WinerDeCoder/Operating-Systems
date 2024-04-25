
#include <stdlib.h>
#include "queue.h"
#include <pthread.h>

/* Remember to initilize the queue before using it */
void initialize_queue(struct pqueue_t * q) {
	q->head = q->tail = NULL;
	pthread_mutex_init(&q->lock, NULL);
}

/* Return non-zero if the queue is empty */
int empty(struct pqueue_t * q) {
	return (q->head == NULL);
}

// get the priority of the head of the queue
int get_priority(struct pqueue_t * q) {
	pthread_mutex_lock(&q->lock);
	if (q->head == NULL) {
		pthread_mutex_unlock(&q->lock);
		return 99;
	}
	pthread_mutex_unlock(&q->lock);
	return q->head->data->priority;
}

/* Get PCB of a process from the queue (q).
 * Return NULL if the queue is empty */
struct pcb_t * de_queue(struct pqueue_t * q) {
	struct pcb_t * proc = NULL;
	// TODO: return q->head->data and remember to update the queue's head
	// and tail if necessary. Remember to use 'lock' to avoid race
	// condition
	pthread_mutex_lock(&q->lock);
	if (q->head != NULL) {
		proc = q->head->data;
		if (q->head == q->tail) {
			q->head = q->tail = NULL;
		} else {
			q->head = q->head->next;
		}
	}
	pthread_mutex_unlock(&q->lock);
	
	// YOUR CODE HERE

	return proc;
}

/* Put PCB of a process to the  ready queue. */
void en_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition
	// preemptive priority scheduling
	// When a process is pushed back to the ready_queue, its priority will be decreased by 1 if the priority is larger than 0	
	pthread_mutex_lock(&q->lock);
	struct qitem_t * item = (struct qitem_t *) malloc(sizeof(struct qitem_t));
	item->data = proc;
	item->next = NULL;
	// push to the queue base on it;s priority
	if (q->head == NULL) {
		q->head = q->tail = item;
	} else {
		struct qitem_t * temp = q->head;
		struct qitem_t * prev = NULL;
		while (temp != NULL && temp->data->priority <= item->data->priority) {
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL) {
			q->tail->next = item;
			q->tail = item;
		} else if (prev == NULL) {
			item->next = q->head;
			q->head = item;
		} else {
			item->next = temp;
			prev->next = item;
			
		}
	}

	pthread_mutex_unlock(&q->lock);
	// YOUR CODE HERE
	
}

//initialize the in queue
void en_in_queue(struct pqueue_t * q, struct pcb_t * proc) {
	// TODO: Update q->tail.
	// Remember to use 'lock' to avoid race condition
	pthread_mutex_lock(&q->lock);
	struct qitem_t * item = (struct qitem_t *) malloc(sizeof(struct qitem_t));
	item->data = proc;
	item->next = NULL;
	if (q->head == NULL) {
		q->head = q->tail = item;
	} else {
		q->tail->next = item;
		q->tail = item;
	}
	pthread_mutex_unlock(&q->lock);
	
	// YOUR CODE HERE
	
}


