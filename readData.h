#ifndef READDATA_H
#define READDATA_H
#include "graph.h"
typedef struct URLList *List;
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
void newURLNode(List l, char *val);
void linkNodes(List l, URL u);
void releaseNode(List l, URL u);
void disposeList(List l);
int nElems(List);
Graph populateGraph(List l);

#endif