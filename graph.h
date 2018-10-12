#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

Graph newGraph(int size);								//create empty graph
void disposeGraph(Graph g);								//free memory occupied by graph
int addEdge(Graph g, char *src, char *dest);			//add an edge between src and dest
int isConnected(Graph g, char *src, char *dest);
int nVertices(Graph g);

#endif