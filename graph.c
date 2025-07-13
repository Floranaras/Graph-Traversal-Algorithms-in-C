#include "graph.h"

void initMatrix (int matrix[][MAX_VERTICES], int size)
{
	int i, j;	

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

int findVertexIdx (graphType *graph, String10 strVertex)
{
	int i;
	int idx = -1;

	for (i = 0; i < graph->nVertices && idx == -1; i++)
	{
		if (!strcmp(graph->vertices[i],strVertex))
		{
			idx = i;
		}
	}

	return idx;
}

int readInputFile (String10 strInputFileName, graphType *graph)
{
	FILE *pFile;
	int i, j;
	String10 strToken;
	String10 tempAdjList[MAX_VERTICES];
	int tempAdjCount;
	int nAdjIndex;
	int nSuccess;

	nSuccess = 0;
	
	pFile = fopen (strInputFileName,"r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &graph->nVertices);

		initMatrix(graph->adjMatrix, MAX_VERTICES);

		for (i = 0; i < graph->nVertices; i++)
		{
			fscanf(pFile,"%s", graph->vertices[i]);

			tempAdjCount = 0;	
			fscanf(pFile, "%s", strToken);

			while (strcmp(strToken,"-1") != 0)
			{
				strcpy(tempAdjList[tempAdjCount],strToken);
				tempAdjCount++;
				fscanf (pFile, "%s", strToken);
			}

			for (j = 0; j < tempAdjCount; j++)
			{
				nAdjIndex = findVertexIdx(graph,tempAdjList[j]);
				if (nAdjIndex != -1)
				{
					graph->adjMatrix[i][nAdjIndex] = 1;
					graph->adjMatrix[nAdjIndex][i] = 1;
				}
			}
		}

		fclose (pFile);
		nSuccess = 1;
	}
	
	return nSuccess;
}
