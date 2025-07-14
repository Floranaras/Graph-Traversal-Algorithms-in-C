#include "graph.h"

void getBaseFileName (String10 baseName, String10 inputName)
{
    int j = 0;

    while (inputName[j] != '.')
    {
        baseName[j] = inputName[j];
        j++;
    }

    baseName[j] = '\0';
}

void initRep (int matrix[][MAX_VERTICES], int *list, int size)
{
    int i, j;

    for (i = 0; i < MAX_VERTICES; i++)
    {
        list[i] = 0;
        for (j = 0; j < MAX_VERTICES; j++)
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

void makeAdjMatrix (graphType *graph)
{
    int i, j;
    int nAdjIdx;

    for (i = 0; i < graph->nVertices; i++)
    {
        for (j = 0; j < graph->adjCount[i]; j++)
        {
            nAdjIdx = findVertexIdx(graph, graph->adjList[i][j]);   

            if (nAdjIdx != -1)
            { 
                graph->adjMatrix[i][nAdjIdx] = 1;
                graph->adjMatrix[nAdjIdx][i] = 1;
            } 
        }
    }
}

int readInputFile (String10 strInputFileName, graphType *graph)
{
	FILE *pFile;
	int i;
	String10 strToken;
	int nSuccess = 0;	

	pFile = fopen (strInputFileName,"r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &graph->nVertices);

	    initRep(graph->adjMatrix, graph->adjCount, MAX_VERTICES);	

        // Read adjacency info from file
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

        makeAdjMatrix (graph);

    	fclose (pFile);
		nSuccess = 1;
	}
	
	return nSuccess;
}

void getOutputFileName (String10 baseName, char *suffix)
{
    strcat(baseName, suffix);
    strcat(baseName,".TXT");
}

void swapNums (int *num1, int *num2)
{
    int temp;
    
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void sortVertices (graphType* graph, int *idx)
{
    int i, j;

    for (i = 0; i < graph->nVertices; i++)
    {
        idx[i] = i;
    }

    for (i = 0; i < graph->nVertices - 1; i++)
    {
        for (j = 0; j < graph->nVertices - 1 - i; j++)
        {
            if (strcmp(graph->vertices[idx[j]],graph->vertices[idx[j+1]]) > 0)
                swapNums(idx+j,idx+j+1); 
        }
    }
}

void produceOutputFile1 (String10 baseName, graphType *graph)
{
    FILE *fp;
    int i, j;
    int nSortedIdx[MAX_VERTICES];
    int nEdgeCtr = 0;
    
    getOutputFileName (baseName,"-SET");

    fp = fopen(baseName,"w");

    if (fp == NULL)
        printf("Output File 1 Error\n");
    else
    {
        // write v(g)
        // write e(g)

        sortVertices(graph, nSortedIdx);
        fprintf(fp,"V(G)={");
        
        for (i = 0; i < graph->nVertices; i++)
        {
            fprintf (fp,"%s",graph->vertices[nSortedIdx[i]]);
            if (i < graph->nVertices - 1)
            {
                fprintf(fp,",");
            }
        }
        fprintf(fp,"}\n");
 
        fprintf(fp,"E(G)={");
        for (i = 0; i < graph->nVertices; i++)
        {
            for (j = i + 1; j < graph->nVertices; j++)
            {
                if (graph->adjMatrix[nSortedIdx[i]][nSortedIdx[j]] == 1)
                {
                    if (nEdgeCtr > 0)
                    {
                        fprintf(fp,",");
                    }

                    fprintf(fp,"(%s,%s)", graph->vertices[nSortedIdx[i]],
                                        graph->vertices[nSortedIdx[j]]);
                    nEdgeCtr++;
                }
            }
        }
        fprintf(fp,"}\n");

        fclose(fp);
    }
}
