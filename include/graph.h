/* graph.h */
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES 20
#define MAX_NAME_LENGTH 8
#define MAX_FILENAME_LENGTH 50

typedef char String10[10];
typedef char String50[50];

/* Graph structure using adjacency matrix */
struct graphTag 
{
    String10 vertices[MAX_VERTICES];
    int nVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    String10 adjList[MAX_VERTICES][MAX_VERTICES]; /* Store adjacency list order */
    int adjCount[MAX_VERTICES]; /* Count of adjacent vertices for each vertex */
};
typedef struct graphTag graphType;

/* Function prototypes */
int readInputFile(String10 strInputFileName, graphType* pGraph);
int findVertexIndex(graphType* pGraph, String10 strVertex);
int produceOutputFile1(String10 strOutputFileName, graphType* pGraph);
int produceOutputFile2(String10 strOutputFileName, graphType* pGraph);
int produceOutputFile3(String10 strOutputFileName, graphType* pGraph);
int produceOutputFile4(String10 strOutputFileName, graphType* pGraph);
int produceOutputFile5(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex);
int produceOutputFile6(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex);
int bfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[]);
int dfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[]);
int createOutputFileName(String10 strInputFileName, char* strSuffix, String50 strOutputFileName);
int sortVerticesAlphabetically(graphType* pGraph, int nIndices[]);
int compareStrings(String10 str1, String10 str2);

#endif