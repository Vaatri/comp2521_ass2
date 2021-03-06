#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "Queue.h"
#include "readData.h"

#define strEQ(g,t) (strcmp((g),(t)) == 0)

Graph newGraph(int size);								//create empty graph
void disposeGraph(Graph g);								//free memory occupied by graph
int addEdge(Graph g, char *src, char *dest);			//add an edge between src and dest
int isConnected(Graph g, char *src, char *dest);		//check if src and dest is connected
int nVertices(Graph g);									//return number of verticies
void showGraph(Graph, int mode);						//show the graph
static int addVertex(char *str, char **urls, int N);	//add str into URL array at index n
static int findVertex(char *str, char **urls, int N);	//check if str is in url Array

//create new graph
Graph newGraph(int size){
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	int i, j;
	new->nV = 0;
	new->maxV = size * (size - 1);
	new->urlVertex = malloc(size * sizeof(char*));
	assert(new->urlVertex != NULL);
	new->edges = malloc(size *sizeof(Num *));
	assert(new->edges != NULL);
	for (i = 0; i < size; i++) {
		new->urlVertex[i] = NULL;
		new->edges[i] = malloc(size * sizeof(Num));
		assert(new->edges[i] != NULL);
		for (j = 0; j < new->maxV; j++)
			new->edges[i][j] = 0;
	}

	return new;
}
//free memory occupied by graph
void disposeGraph(Graph g) {

	if (g == NULL) return;
	int i;
	for (i = 0; i < g->nV; i++) {
		free(g->urlVertex[i]);
	}
	for (i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}
	free(g->edges);
}
/*	Adding an edge from src to dest in matrix array
	returns 1 if successful
	returns 0 if unsucessful
*/	
int addEdge(Graph g, char *src, char *dest) {
	assert(g != NULL);
	int v = findVertex(src, g->urlVertex, g->nV);
	if (v < 0) {
		if (g->nV >= g->maxV) return 0;
		v = addVertex(src, g->urlVertex, g->nV);
		g->nV++;
	}
	int w = findVertex(dest, g->urlVertex, g->nV);
	if (w < 0) {
		if (g->nV >= g->maxV) return 0;
		w = addVertex(dest, g->urlVertex, g->nV);
		g->nV++;
	}
	g->edges[v][w] = 1;
	return 1;
}

//check if theres an edge between src and dest
int isConnected(Graph g, char *src, char *dest) {
	assert(g != NULL);
	int v = findVertex(src, g->urlVertex, g->nV);
	int w = findVertex(dest, g->urlVertex, g->nV);
	if (v < 0 || w < 0) 
		return 0;
	else
		return g->edges[v][w];
}

int nVertices(Graph g) {
	assert(g != NULL);
	return (g->nV);
}

void showGraph(Graph g, int mode) {
	assert(g != NULL);
	if (g->nV == 0)
		printf("Graph is empty\n");
	else {
		printf("Graph has %d vertices:\n",g->nV);
		int i, j;
		if (mode == 1) {
			for (i = 0; i < g->nV; i++) {
				for (j = 0; j < g->nV; j++)
					printf("%d",g->edges[i][j]);
				putchar('\n');
			}
		}
		else {
			for (i = 0; i < g->nV; i++) {
				printf("Vertex: %s\n", g->urlVertex[i]);
				printf("connects to\n");
				for (j = 0; j < g->nV; j++) {
					if (g->edges[i][j])
						printf("   %s\n",g->urlVertex[j]);
				}
			}
		}
	}
}

//searches str in string array
//returns index of str or -1 depending on found or not
static int findVertex(char *str, char **urls, int N){
	int i;
	for (i = 0; i < N; i++)
		if (strEQ(str, urls[i])) return i;
	return -1;
}

static int addVertex(char *str, char **urls, int N) {
	urls[N] = strdup(str);
	return N;
}

