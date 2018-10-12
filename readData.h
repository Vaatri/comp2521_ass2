#ifndef READDATA_H
#define READDATA_H

typedef struct URLList *List;

List newList();
void newURLNode(List l, char *val, int index);
void linkNodes(list l, URL u);
void releaseNode(URL);
void disposeList(list l);
int nElems(list);

#endif