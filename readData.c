//read in data from collection.txt
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include "queue.h"

#define strEQ(s,t) (strcmp((s), (t)) == 0)

//URLList is essentially a set
struct urlNode{
	char *url; 	//hold the string value of URL
	URL next; 	//pointer to next node
};

struct URLList {
	int nitems;	//# of items in list
	URL head;	//pointer to head
	URL curr;	//after linking nodes, this will point to the last.
};

List newList();							//create a list with collection.txt
void newURLNode(List l, char *);		//create node with given str
void linkNodes(List l, URL);			//link node in List
void releaseNode(List l, URL);				//free occupied memory of node
void disposeList(List l);				//free occupied memory of list
int nElems(List l);						//return size of list
void populateGraph(List l);

static void readData(List);
static void printlist(List);
static int findNode(URL u, char *str);

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
	char *input = malloc(8);
	while(fscanf(fp, "%s", input) != EOF) {
		newURLNode(l, input);
	}
	//printlist(l);
	populateGraph(l);
}

void populateGraph(List l){
	//string to hold dequeued string
	char *parent;
	//string to hold urls from file
	char *fileInput = malloc(1);
	//string used to open the file
	//dont want to change the parent value
	char *fileSearch = malloc(1);
	Graph g = newGraph(l->nitems);
	Queue q = newQueue();

	URL curr = l->head;
	enterQueue(q, curr->url);
	//printf("hello1\n");
	while(!emptyQueue(q)) {
		//if theres more verticies than nodes break
		if (nVertices(g) >= l->nitems) break;
		//need to concatenate .txt onto curr->URL
		parent = strdup(leaveQueue(q));						//dequeue url
		int strLen = strlen(curr->url) + 5;					//find length to store filename
		fileSearch = (char *) realloc(fileSearch, strLen);	
		strcpy(fileSearch, parent);							//copy parent url to filesearch
		strcat(fileSearch, ".txt");							//concatenate .txt to url so url11 -> url11.txt
		//open file using parent
		FILE *fp = fopen(fileSearch, "r");					//open file using fileSearch value
		if(fp == NULL){
			printf("filepath is invalid");
			break;
		}
		fileInput = (char *) realloc(fileInput, strlen(curr->url));
		while(fscanf(fp, "%s", fileInput) != EOF){			//search file for "url" only
			if (strstr(fileInput, "url") != NULL) {				
				if (isConnected(g, parent, fileInput) == 0){		//isConnected will return true if src & dest isnt connected 
					addEdge(g, parent, fileInput);			//add edge between parent and url inside txt file
					enterQueue(q, fileInput);				//add url into queue
					//showQueue(q);
				}
			}
		}
	}
	//this will show the graph once it is completed
	showGraph(g, 1);

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
