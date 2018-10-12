//read in data from collection.txt
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"

typedef struct urlNode *URL;

struct urlNode{
	char *url; 	//hold the string value of URL
	URL next; 	//pointer to next node
};

struct URLList {
	int nitems;	//# of items in list
	URL head;	//pointer to head
	URL curr;	//after linking nodes, this will point to the last.
};

List newList();
void newURLNode(List l, char *);
void linkNodes(list l, URL u);
void releaseNode(URL u);
void disposeList(list l);
int nElems(list);


static void readData()


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

void linkNodes(list l, URL u){

	if (l->head == NULL) {
		l->head = l->curr = u;
	} else {
		l->curr->next = u;
		l->curr = u;
	}
}

static void readData(list l){
	
	FILE *fp = fopen("collection.txt", "r");
	char *input;
	while(fscanf(fp, "%s", input) != EOF) {
		newURLNode(l, input);
	}
}

int nElems(list l) {
	assert(l != NULL)
	return l->nitems;
}

void disposeList(list l){
	URL curr = l->head;

	//free nodes in the list.
	while(curr->next != NULL) {
		URL temp = curr->next;
		releaseNode(curr);
		curr = temp;
		curr = curr->next;
	}
	releaseNode(curr);
	free(l);

}	
void releaseNode(URL u) {
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