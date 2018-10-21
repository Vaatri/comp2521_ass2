//read in data from collection.txt
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include "queue.h"
#include "pagerank.h"

#define strEQ(s,t) (strcmp((s), (t)) == 0)

//URLList is essentially a set


List newList();							//create a list with collection.txt
void newURLNode(List l, char *);		//create node with given str
void linkNodes(List l, URL);			//link node in List
void releaseNode(List l, URL);				//free occupied memory of node
void disposeList(List l);				//free occupied memory of list
int nElems(List l);						//return size of list
Graph populateGraph(List l);				//this will create the graph

static void readData(List);
static void printlist(List);
static int findNode(URL u, char *str);

int main(int argc, char **argv){

	int max;
	double d, diff;
	if (argc < 4 || argc > 4) {
		printf("incorrect number of cmd-line arguements\n");
	} else{
		d = atof(argv[1]);
		diff = atof(argv[2]);
		max = atoi(argv[3]);
	}
	//create new list
	List l = newList();
	// printlist(l);
	//create the graph
	// printlist(l);
	Graph g = populateGraph(l);
	//calculate the page rank

	calculatePageRank(g, d, diff, max);
	disposeList(l);
	disposeGraph(g);


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
	char *input = malloc(6);
	while(fscanf(fp, "%s", input) != EOF) {
		newURLNode(l, input);
	}
	fclose(fp);
	//printlist(l);
	//populateGraph(l);
}

Graph populateGraph(List l){
	//string to hold dequeued string
	char *parent;
	//string to hold urls from file
	char *fileInput = malloc(6);
	//string used to open the file
	//dont want to change the parent value
	char *fileSearch = malloc(10);
	Graph g = newGraph(l->nitems);
	Queue q = newQueue();

	URL curr = l->head;
	while(curr != NULL){
		enterQueue(q, curr->url);
		curr = curr->next;
	}

	while(!emptyQueue(q)) {
		parent = strdup(leaveQueue(q));	
		strcpy(fileSearch, parent);
		strcat(fileSearch, ".txt");
		FILE *fp = fopen(fileSearch, "r");
		if(fp == NULL) {
			printf("filepath is invalid\n");
		}
		while(fscanf(fp, "%s", fileInput) != EOF){
			if (strstr(fileInput, "url") != NULL) {
				if(isConnected(g, parent, fileInput) == 0) {
					addEdge(g, parent, fileInput);
				}
			}
		}
	}	

	if (!emptyQueue(q)) disposeQueue(q);
	free(parent);
	free(fileSearch);
	free(fileInput);
	//this will show the graph once it is completed
	showGraph(g, 1);

	return g;
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
//function to see whether string is in the elist
int isElem(List l, char *str){
	assert(l != NULL);
	return findNode(l->head,str);
}


//debug functions/helper func

static void printlist(List l){
	URL curr = l->head;
	// printf("head points to = %s\n curr points to %s\n", l->head, l->curr);
	printf("list size = %d\n", l->nitems);
	while(curr != NULL){
		printf("curr = %s\n", curr->url);
		curr = curr->next;
	}
}

static int findNode(URL u, char *str){
	URL current = u;
	while (current != NULL) {
		if(strEQ(str, current->url)) return 0;
	}
	return 1;
}
