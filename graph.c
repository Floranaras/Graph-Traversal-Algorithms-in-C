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
	int i, j;
	String10 strToken;
	int nSuccess = 0;	
    int nAdjIdx;

	pFile = fopen (strInputFileName,"r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &graph->nVertices);

		for (i = 0; i < MAX_VERTICES; i++)
		{
			graph->adjCount[i] = 0;
            for (j = 0; j < MAX_VERTICES; j++)
            {
                graph->adjMatrix[i][j] = 0;
            }
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

        for (i = 0; i < graph->nVertices; i++)
        {
            for (j = 0; j < graph->nVertices; j++)
            {
                nAdjIdx = findVertexIdx(graph, graph->adjList[i][j]);   
                
                if (nAdjIdx != -1)
                { 
                    graph->adjMatrix[i][nAdjIdx] = 1;
                    graph->adjMatrix[nAdjIdx][i] = 1;
                } 
            }
        }

		fclose (pFile);
		nSuccess = 1;
	}
	
	return nSuccess;
}


