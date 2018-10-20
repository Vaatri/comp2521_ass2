#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

typedef unsigned char Num;

typedef struct GraphRep {
	int nV;				//store # of vertices
	int maxV;			//store max number of vertices
	char **urlVertex;	//String array to store urls
	Num **edges;		//adjacency matrix
} GraphRep;

Graph newGraph(int size);								//create empty graph
void disposeGraph(Graph g);								//free memory occupied by graph
int addEdge(Graph g, char *src, char *dest);			//add an edge between src and dest
int isConnected(Graph g, char *src, char *dest);
int nVertices(Graph g);
void showGraph(Graph, int mode);

#endif