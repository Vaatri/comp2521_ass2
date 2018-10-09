//Queue header file
//Taken from queue.h week07 LAB

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueRep *Queue;

Queue newQueue(); 					//initialize new EMPTY queue
void disposeQueue(Queue);			//Clear queue
void enterQueue(Queue, char *);		//Enqueue Value
char *leaveQueue(Queue);			//Dequeue first value in queue
int emptyQueue(Queue);				//check if queue is empty
void showQueue(Queue q);			//show the current queue

#endif
