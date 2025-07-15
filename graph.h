#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES (20)
#define MAX_STR (51)

typedef char String50[MAX_STR];

struct graphTag
{
	String50 vertices[MAX_VERTICES];
    int nVertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    String50 adjList[MAX_VERTICES][MAX_VERTICES];
    int adjCount[MAX_VERTICES];
};

typedef struct graphTag graphType;

/* Function Prototypes */
