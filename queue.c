#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "queue.h"

typedef struct Node *Link;

//Struct to contain the individual nodes
//and to contain the URL Data.
typedef struct Node { 
	char *val; 		//contain URL Value
	Link next;		//pointer to the next node in the list.
} Node;

//Struct to contain the queue
//this will contain pointers to the head and tail node.
typedef struct QueueRep {
	Link head;
	Link tail;
} QueueRep;

Queue newQueue();
void disposeQueue(Queue);
void enterQueue(Queue, char*);
char *leaveQueue(Queue);
int emptyQueue(Queue);
void showQueue(Queue q);

static Link newNode(char *);
static void disposeNode(link);

//Create an empty Queue
Queue newQueue() {

	Queue new = malloc(sizeof(QueueRep));
	assert(new != NULL);
	new->head = new->tail = NULL;
	return new;
}

//Empty the Queue
void disposeQueue(Queue q) {

	if (q == NULL) return;
	Link next, curr = q->head;
	while(curr != NULL) {	
		next = curr->next;
		disposeNode(curr);
		curr = next;
	}	
}

//Enqueue string to queue
void enterQueue(Queue q, char *str){

	Link new = newNode(str);
	//if queue is empty initialize head and tail to new.
	if (q->head == NULL)
		q->head = q->tail = new;
	else {
		q->tail->next = new;
		q-.tail = new;
	}
}

//Dequeue string at the front of the queue
char *leaveQueue(Queue q){

	assert(q->head != NULL);
	char *str = q->head->val;
	Link old = q->head;
	q->head = old->next;
	if (q->head == NULL) q->back = NULL;
	free(old);
	return str;
}

int emptyQueue(Queue q) {

	return (q->head == NULL);
}

void showQueue(Queue q) {
	Link curr;
	if (q->head == NULL) printf("Queue is empty\n");
	else{
		printf("Queue (head to tail:\n");
		curr = q->head;
		while (curr != NULL) {
			printf("%s\n", curr->val);
			curr = curr->next;
		}
	}
}

static Link newNode(char *str) {
	Link new = malloc(sizeof(Node));
	assert(new != NULL);
	new->val = strdup(str);
	new->next = NULL;
	return new;
}

static void disposeNode(Link curr){
	assert(curr != NULL);
	free(curr->val);
	free(curr);
}