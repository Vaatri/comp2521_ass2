//read in data from collection.txt
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"


struct urlNode{
	char *url; 	//hold the string value of URL
	URL next; 	//pointer to next node
};

struct URLList {
	int nitems;	//# of items in list
	URL head;	//pointer to head
	URL curr;	//after linking nodes, this will point to the last.
};

List newList();							//create empty linked list
void newURLNode(List l, char *);		//create node with given str
void linkNodes(List l, URL);			//link node in List
void releaseNode(List l, URL);				//free occupied memory of node
void disposeList(List l);				//free occupied memory of list
int nElems(List l);						//return size of list


static void readData(List);
static void printlist(List);

int main(){

	List l = newList();
	return 0;
}


List newList(){

	List new = malloc(sizeof(struct URLList));
	assert(new != NULL);
	new->nitems = 0;
	new->head = new->curr = NULL;
	readData(new);
	return new;
}	

void newURLNode(List l, char *val){

	URL new = malloc(sizeof(struct urlNode));
	assert(new != NULL);
	new->url = strdup(val);
	new->next = NULL;
	l->nitems++;
	linkNodes(l, new);

}

void linkNodes(List l, URL u){

	if (l->head == NULL) {
		l->head = l->curr = u;
	} else {
		l->curr->next = u;
		l->curr = u;
	}
}

static void readData(List l){
	
	FILE *fp = fopen("collection.txt", "r");
	assert(fp != NULL);
	printf("hello\n");
	char *input = malloc(8);
	while(fscanf(fp, "%s", input) != EOF) {
		newURLNode(l, input);
	}
	printlist(l);
}

int nElems(List l) {
	assert(l != NULL);
	return l->nitems;
}

void disposeList(List l){
	URL curr = l->head;

	//free nodes in the list.
	while(curr->next != NULL) {
		URL temp = curr->next;
		releaseNode(l, curr);
		curr = temp;
		curr = curr->next;
	}
	releaseNode(l, curr);
	free(l);

}	
void releaseNode(List l, URL u) {
	if (u->next == NULL) {
		free(u->url);
		free(u);
		l->nitems--;
		l->head = l->curr = NULL;
	} else {
		free(u->url);
		free(u);
	}

}


//debug functions

static void printlist(List l){
	URL curr = l->head;
	while(curr != NULL){
		printf("curr = %s\n", curr->url);
		curr = curr->next;
	}
}