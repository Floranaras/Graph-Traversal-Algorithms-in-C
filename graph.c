#include "graph.h"

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
	int i;
	String10 strToken;
	int nSuccess;

	nSuccess = 0;
	
	pFile = fopen (strInputFileName,"r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &graph->nVertices);

		for (i = 0; i < MAX_VERTICES; i++)
		{
			graph->adjCount[i] = 0;
		}

		for (i = 0; i < graph->nVertices; i++)
		{
			fscanf(pFile,"%s", graph->vertices[i]);

			graph->adjCount[i] = 0;
			fscanf(pFile, "%s", strToken);

			while (strcmp(strToken,"-1") != 0)
			{
				strcpy(graph->adjList[i][graph->adjCount[i]],strToken);
				graph->adjCount[i]++;
				fscanf (pFile, "%s", strToken);
			}

		}

		fclose (pFile);
		nSuccess = 1;
	}
	
	return nSuccess;
}
