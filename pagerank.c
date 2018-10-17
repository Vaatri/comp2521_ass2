#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "readData.h"
#include "graph.h"
#include "queue.h"
#include "pagerank.h"

//macros
#define initialPRVal(n,d) (((1 - d)/n) + d)

void calculatePageRank(URL u, int d, int diff, int max, int size);
static int findSumPR(Graph g, int pageIndex, int **pageRank, int iteration);


static int calcWin(Graph g, int u, int v);
static int inLinks(Graph g, int index);
static int calcWout(Graph g, int u, int v);
static int outLinks(Graph g, int index);
//calculate pagerank for every node

//calculate pagerank for the node passed in
void calculatePageRank(Graph g, URL u, int d, int diffPR, int max){
	int size = g->nV;

	//store the pageRank in a 2d Array
	//the first column of the array will be the initial pageRank
	int **pageRank = malloc(size * sizeof(int));
	for(int i = 0; i < g->nV; i++) {
		pageRank[i] = malloc(max * sizeof(int));
		pageRank[i][0] = 1/size;
	}


	int iteration = 0;
	int diff = diffPR;

	while(iteration < max && diff >= diffPR) {
		for(int i = 0; i < size; i++){
			pageRank[i][iteration + 1] = initialPRVal(size, d) *findSumPR(g, i, pageRank, iteration);
			diff = fabs((pageRank[i][iteration + 1] - pageRank[i][iteration]));
		}
		iteration++;
	}
	FILE *fp = fopen("pagerankList.txt", "w+");

	for(int i=0; i<g->nV; i++) {
		fprintf(fp, "%s, %d, %.7f" )
	}
}

//find all of the outgoing links to pi, and use them as pj
//use the pagerank of pj (from the index you found when finding the outgoing links TO pi)
//to find the initial pageRank for the formula.
//find the Win && Wout for the relevent pj and pi, 
//multiply them together, and add them to the sum
static int findSumPR(Graph g, int pageIndex, int **pageRank, int iteration){
	int sum = 0;
	//find pj
	for (int i = 0; i < g->nV; i++) {
		if (g->edges[pageIndex][i]) == 1;
		//page index is pi, i is pj
			sum =+ pageRank[i] * calcWin(g, pageIndex, i) * calcWout(g, pageIndex, i);
	}

	return sum;

}

static int calcWin(Graph g, int u, int v){
	//get inlinks to u
	int uInlink = inLinks(g, u);
	//get inlinks to the references of v
	int vInlink = 0;

	for (int i = 0; i<g->nV; i++) {
		if (!g->edges[v][i])continue;
		vInlink = inLinks(g, i);
	}
	return uInlink/vInlink;
}

static int inLinks(Graph g, int index){
	int inlinks = 0;
	for(int i = 0; i < g->nV; i++) {
		if (g->edges[i][index] == 1) {
			inLinks++;
		}
	}
	return inLinks;
}

static int calcWout(Graph g, int u, int v){
	int uOutlink = outLinks(g, pageIndex);
	int vOutlink = 0;

	for (int i = 0; i < g->nV; i++) {
		if (!g->edges[v][i]) continue;
		vOutlink = outLinks(g, i);
	}	

	return uOutlink/vOutlink;
}

static int outLinks(Graph g, int index) {
	int outLinks = 0;
	for (int i = 0; i<g->nV; i++) {
		if (g->edges[index][i] == 1) {
			outLinks++
		}
	}
	return outLinks;

}