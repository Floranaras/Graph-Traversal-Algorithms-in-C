#include "graph.h"

int readInputFile (String10 strInputFileName, graphType *graph)
{
	FILE *pFile;
	int i, j, k;
	int bFound = 0;
	String10 strToken;
	int nSuccess;
	int nAdjIndex;

	nSuccess = 0;
	
	pFile = fopen (strInputFileName,"r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &graph->nVertices);

		// Initialization why no helper func allow
		for (i = 0; i < MAX_VERTICES; i++)
		{
			graph->adjCount[j] = 0;
			for (j = 0; j < MAX_VERTICES; j++)
			{
				graph->adjMatrix[i][j] = 0;
			}
		}

		// Adjacency info
		for (i = 0; i < graph->nVertices; i++)
		{
			fscanf(pFile, "%s", strToken);

			while (strcmp(strToken,"-1") != 0)
			{
				strcpy(graph->adjList[i][graph->adjCount[i]],strToken);
				graph->adjCount[i]++;
				fscanf (pFile, "%s", strToken);
			}
		}

		// Make Adjacency Matrix
		
		for (i = 0; i < graph->nVertices; i++)
		{
			for (j = 0; j < graph->adjCount[i]; j++)
			{
				bFound = 0;
				for (k = 0; k < graph->nVertices && bFound; k++)
				{
					if (!strcmp(graph->vertices[k],graph->adjList[i][j]))
					{
						nAdjIndex = k;
						bFound = 1;
					}
				}

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
