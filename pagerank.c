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

void calculatePageRank(Graph g, double d, double diffPR, int max);


static double findSumPR(Graph g, int pageIndex, double **pageRank, int iteration);
static double calcWin(Graph g, int u, int v);
static int inLinks(Graph g, int index);
static double calcWout(Graph g, int u, int v);
static int outLinks(Graph g, int index);


//calculate pagerank for the node passed in
void calculatePageRank(Graph g, double d, double diffPR, int max){
	double size = nVertices(g);
	//store the pageRank in a 2d Array
	//the first column of the array will be the initial pageRank
	double **pageRank = malloc(size * sizeof(double));
	//value for initial PR
	for(int i = 0; i < g->nV; i++) {
		pageRank[i] = malloc(max * sizeof(double));
		for(int j = 0; j < max; j++){
			pageRank[i][j] = 0;
		}
		pageRank[i][0] = 1/size;
	}

	int iteration = 0;
	double diff = diffPR;

	while(iteration < max && diff >= diffPR) {
		for(int i = 0; i < size; i++){
			pageRank[i][iteration + 1] = initialPRVal(size, d) * findSumPR(g, i, pageRank, iteration);
			// printf("initialPRVal = %f\n", initialPRVal(size, d));
			printf("for pagerank[%s] pr[%d][%d] = %f, at iteration + 1 pr[%d][%d] = %f\n", g->urlVertex[i], i, iteration, pageRank[i][iteration], i, iteration + 1, pageRank[i][iteration + 1]);
		}
		for(int i = 0; i < size; i++){
			diff += fabs((pageRank[i][iteration + 1] - pageRank[i][iteration]));		
		}
		iteration++;
	}
	printf("iteration = %d\n", iteration);
	FILE *fp = fopen("pagerankList.txt", "w+");
	if (fp == NULL) {
		printf("file path failed\n");
	}

	for(int i = 0; i < g->nV; i++) {
		fprintf(fp, "%s, %d, %.7f\n", g->urlVertex[i], outLinks(g, i), pageRank[i][iteration]);
	}

	fclose(fp);
}

//find all of the outgoing links to pi, and use them as pj
//use the pagerank of pj (from the index you found when finding the outgoing links TO pi)
//to find the initial pageRank for the formula.
//find the Win && Wout for the relevent pj and pi, 
//multiply them together, and add them to the sum
static double findSumPR(Graph g, int pageIndex, double **pageRank, int iteration){
	double sum = 0;
	printf("pageindex = %d\n", pageIndex);
	//find pj
	printf("iteration = %d\n", iteration);
	printf("g->nV = %d\n", nVertices(g));
	for (int i = 0; i < nVertices(g); i++) {
		if (g->edges[pageIndex][i] == 1){
		//page index is pi, i is pj
			sum += (pageRank[i][iteration] * calcWin(g, pageIndex, i) * calcWout(g, pageIndex, i));
			printf("pageRank[%d][%d] = %f calcWin = %f, calcOut = %f\n", i, iteration, pageRank[i][iteration], calcWin(g, pageIndex, i), calcWout(g, pageIndex, i));
			// printf("sum = %f\n", sum);
		}	
	}
	//so if there are no connections edges from pageindex to i; 
	//still have to find the Win and Wout
	// if (sum == 0){

	// }
	// if (sum == 0) {
	// 	sum = 0.5;
	// }
	return sum;

}

static double calcWin(Graph g, int u, int v){
	//get inlinks to u
	double uInlink = inLinks(g, u);
	//get inlinks to the references of v
	double vInlink = 0;

	for (int i = 0; i < g->nV; i++) {
		if (!g->edges[v][i])continue;
		vInlink += inLinks(g, i);
	}
	// if (vInlink == 0) {
	// 	vInlink = 0.5;
	// 	return vInlink;
	// }
	//printf("uinlink = %f vinlink = %f Win = %f\n", uInlink, vInlink, uInlink/vInlink);
	return uInlink/vInlink;
}

static int inLinks(Graph g, int index){
	int links = 0;
	for(int i = 0; i < g->nV; i++) {
		if (g->edges[i][index] == 1) {
			links++;
		}
	}
	return links;
}

static double calcWout(Graph g, int u, int v){
	double uOutlink = outLinks(g, u);
	double vOutlink = 0;

	for (int i = 0; i < g->nV; i++) {
		if (!g->edges[v][i]) continue;
		vOutlink += outLinks(g, i);
	}	

	if (uOutlink == 0) {
		uOutlink = 0.5;
		return uOutlink;
	}
	//printf("uOutlink = %f vOutlink = %f Wout = %f\n", uOutlink, vOutlink, uOutlink/vOutlink);
	return uOutlink/vOutlink;
}

static int outLinks(Graph g, int index) {
	int links = 0;
	for (int i = 0; i < g->nV; i++) {
		if (g->edges[index][i] == 1) {
			links++;
		}
	}
	return links;

}


