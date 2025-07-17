#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES (20)
#define MAX_STR (51)

typedef char String50[MAX_STR];

struct adjNode 
{
    String50 vertex;
    struct adjNode* next;
};

typedef struct adjNode adjNode;

struct graphTag
{
    String50 vertices[MAX_VERTICES];
    int nVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    adjNode *adjList[MAX_VERTICES];
    int adjCount[MAX_VERTICES];
};

typedef struct graphTag graphType;

/* Function Prototypes */

/* File Loading Functions */
void initRep (int matrix[][MAX_VERTICES], int *list, int size);
int findVertexIdx (graphType *graph, String50 strVertex);
void makeAdjMatrix (graphType *graph);
int readInputFile (String50 strInputFileName, graphType *graph);

/* File Output Helper Functions */
void getBaseFileName (String50 baseName, String50 inputName);
void getOutputFileName (String50 baseName, char *suffix);
void swapNums (int *num1, int *num2);
void sortVertices (graphType* graph, int *idx);
int collectAdjacentVertices(adjNode* adjList, String50 adjVertices[]);
void printVertexAdjacencyList(FILE* fp, String50 vertex, String50 adjVertices[], int adjCount);

/* Linked list helper functions */
adjNode* createNode (String50 vertex);
void addToAdjList (graphType *graph, int vertexIdx, String50 adjVertex);
void freeAdjLists (graphType *graph);

/* Algorithm Functions */
void BFS(graphType *graph, int startingIndex, String50 result[]);

/* Output Functions */
void produceOutputFile1 (String50 baseName, graphType *graph);
void produceOutputFile2 (String50 baseName, graphType *graph);
void produceOutputFile3 (String50 baseName, graphType *graph);
void produceOutputFile4 (String50 baseName, graphType *graph);
void produceOutputFile5 (String50 baseName, graphType *graph, String50 start);
