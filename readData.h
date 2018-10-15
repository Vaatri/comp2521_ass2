#ifndef READDATA_H
#define READDATA_H

typedef struct URLList *List;
typedef struct urlNode *URL;

List newList();
void newURLNode(List l, char *val);
void linkNodes(List l, URL u);
void releaseNode(List l, URL u);
void disposeList(List l);
int nElems(List);

#endif