#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_VERTICES (20)
#define MAX_NAME_LENGTH (8)
#define MAX_FILENAME_LENGTH (50)

typedef char String10[MAX_NAME_LENGTH];
typedef char String50[MAX_FILENAME_LENGTH];

struct graphTag
{
	String10 vertices[MAX_VERTICES];
	int nVertices;
	int adjMatrix[MAX_VERTICES][MAX_VERTICES];
	String10 adjList[MAX_VERTICES][MAX_VERTICES];
	int adjCount[MAX_VERTICES];
};

typedef struct graphTag graphType;

/* Function Prototypes */
