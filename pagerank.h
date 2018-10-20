#ifndef PAGERANK_H
#define PAGERANK_H
#include "graph.h"
#include "readData.h"

void calculatePageRank(Graph g, double d, double diffPR, int max);

#endif