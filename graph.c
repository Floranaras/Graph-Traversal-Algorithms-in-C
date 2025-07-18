#include "graph.h"

void getBaseFileName (String50 baseName, String50 inputName)
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

adjNode* createNode (String50 vertex)
{
    adjNode* newNode = (adjNode*)malloc(sizeof(adjNode));
    
    if (newNode != NULL)
    {
        strcpy (newNode->vertex, vertex);
        newNode->next = NULL;
    }

    return newNode;
}

void addToAdjList(graphType *graph, int vertexIdx, String50 adjVertex)
{
    adjNode* newNode;
    adjNode* current;

    newNode = createNode (adjVertex);

    if (newNode != NULL) 
    {
        if (graph->adjList[vertexIdx] == NULL) 
            graph->adjList[vertexIdx] = newNode;

        else 
        {
            current = graph->adjList[vertexIdx];

            while (current->next != NULL)
                current = current->next;

            current->next = newNode;
        }

        graph->adjCount[vertexIdx]++;
    }
}

void freeAdjList(graphType *graph)
{
    int i;
    adjNode* current;
    adjNode* next;

    for (i = 0; i < MAX_VERTICES; i++)
    {
        current = graph->adjList[i];
        
        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }

        graph->adjList[i] = NULL;
        graph->adjCount[i] = 0;
    }
}

int findVertexIdx (graphType *graph, String50 strVertex)
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
    adjNode* current;

    for (i = 0; i < MAX_VERTICES; i++)
    {
        for (j = 0; j < MAX_VERTICES; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }

    for (i = 0; i < graph->nVertices; i++)
    {
        current = graph->adjList[i];
        while (current != NULL)
        {
            nAdjIdx = findVertexIdx (graph, current->vertex);

            if (nAdjIdx != -1)
            {
                graph->adjMatrix[i][nAdjIdx] = 1;
                graph->adjMatrix[nAdjIdx][i] = 1;
            }

            current = current->next;
        }
    }
}

int readInputFile (String50 strInputFileName, graphType *graph)
{
    FILE *pFile;
    int i;
    String50 strToken;
    int nSuccess = 0;

    pFile = fopen (strInputFileName,"r");

    if (pFile != NULL)
    {
        fscanf(pFile, "%d", &graph->nVertices);

        initRep(graph->adjMatrix, graph->adjCount, MAX_VERTICES);	

        for (i = 0; i < MAX_VERTICES; i++)
        {
            graph->adjList[i] = NULL;
        }

        // Read adjacency info from file
        for (i = 0; i < graph->nVertices; i++)
        {
            fscanf(pFile,"%s", graph->vertices[i]);

            graph->adjCount[i] = 0;
            fscanf(pFile, "%s", strToken);

            while (strcmp(strToken,"-1") != 0)
            {
                addToAdjList(graph, i, strToken);
                fscanf (pFile, "%s", strToken);
            }
        }

        makeAdjMatrix (graph);

        fclose (pFile);
        nSuccess = 1;
    }

    return nSuccess;
}

void getOutputFileName (String50 baseName, char *suffix)
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


void produceOutputFile1 (String50 baseName, graphType *graph)
{
    FILE *fp;
    int i, j;
    int nSortedIdx[MAX_VERTICES];
    int nEdgeCtr = 0;
    String50 outputName;

    strcpy(outputName, baseName);

    getOutputFileName (outputName,"-SET");

    fp = fopen(outputName,"w");

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

int collectAdjacentVertices(adjNode* adjList, String50 adjVertices[])
{
    adjNode* current;
    int adjCount;
    
    adjCount = 0;
    current = adjList;
    while (current != NULL) {
        strcpy(adjVertices[adjCount], current->vertex);
        adjCount++;
        current = current->next;
    }
    
    return adjCount;
}

void printVertexAdjacencyList(FILE* fp, String50 vertex, String50 adjVertices[], int adjCount)
{
    int j;
    
    // Print first vertex
    fprintf(fp, "%s->", vertex);
    
    // Print all vertices with an edge to the first vertex
    for(j = 0; j < adjCount; j++){
        fprintf(fp, "%s->", adjVertices[j]);
        
        if(j == (adjCount - 1))
            fprintf(fp, "\\");
    }
}

void produceOutputFile2 (String50 baseName, graphType *graph)
{
    FILE *fp;
    int i;
    int nSortedIdx[MAX_VERTICES];
    String50 outputName;
    
    // Get file name of output file
    strcpy(outputName, baseName);
    getOutputFileName(outputName, "-DEGREE");
    
    // Open output file
    fp = fopen(outputName,"w");

    if (fp == NULL)
        printf("Output File 2 Error\n");

    else
    {
        // Get indices of sorted vertex
        sortVertices(graph, nSortedIdx);
        
        // Print vertices in ascending order along with their degrees
        for(i = 0; i < graph->nVertices; i++)
        {
            fprintf(fp, "%-10s", graph->vertices[nSortedIdx[i]]);
            fprintf(fp, "%d", graph->adjCount[nSortedIdx[i]]);

            if(i < graph->nVertices - 1)
                fprintf(fp, "\n");
        } 
        // Close output file
        fclose(fp);
    }
}

void produceOutputFile3 (String50 baseName, graphType *graph)
{
    FILE *fp;
    int i;
    String50 outputName;
    String50 adjVertices[MAX_VERTICES];
    int adjCount;
    
    // Get file name of output file
    strcpy(outputName, baseName);
    getOutputFileName(outputName, "-LIST");
    
    // Open output file
    fp = fopen(outputName,"w");
    if (fp == NULL)
        printf("Output File 3 Error\n");

    else
    {
        // Print vertices in their original input order (no sorting of vertices)
        for(i = 0; i < graph->nVertices; i++)
        {
            // Collect all adjacent vertices from linked list
            adjCount = collectAdjacentVertices(graph->adjList[i], adjVertices);
            
            // Print adjacency list for this vertex
            printVertexAdjacencyList(fp, graph->vertices[i], adjVertices, adjCount);
            
            if(i < (graph->nVertices - 1))
                fprintf(fp, "\n");
        }
        
        // Close output file
        fclose(fp);
    }
}

void produceOutputFile4 (String50 baseName, graphType *graph) 
{
    FILE *fp;
    String50 outputName;
    int i;

    strcpy(outputName, baseName);

    getOutputFileName(outputName,"-MATRIX");

    fp = fopen(outputName,"w");

    fprintf(fp, "%-10s", "");

    for (i = 0; i < graph->nVertices; i++) {
        fprintf(fp, "%-10s", graph->vertices[i]);
    }

    fprintf(fp, "\n");

    for (i = 0; i < graph->nVertices; i++) {

        fprintf(fp, "%-10s", graph->vertices[i]);

        for (int j = 0; j < graph->nVertices; j++) {
            fprintf(fp, "%-10d", graph->adjMatrix[i][j]);
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
}

void BFS(graphType *graph, int startingIndex, String50 result[]) 

{
    int visited[MAX_VERTICES];
    int queue[MAX_VERTICES];
    int frontOfQueue = 0;
    int tailofQueue = 0;
    int resultCtr = 0;
    int currentVertex;
    int candidates[MAX_VERTICES];
    int candidatesCtr, i;
    int j, minIdx, temp;

    for (i = 0; i < graph->nVertices; i++) 
    {
        visited[i] = 0;
    }

    queue[tailofQueue] = startingIndex;
    tailofQueue++;
    visited[startingIndex] = 1;

    while (frontOfQueue < tailofQueue) 
    {
        currentVertex = queue[frontOfQueue];
        frontOfQueue++;

        strcpy(result[resultCtr], graph->vertices[currentVertex]);
        resultCtr++;

        candidatesCtr = 0;
        for (i = 0; i < graph->nVertices; i++) 
        {
            if (graph->adjMatrix[currentVertex][i] && !visited[i]) 
            {
                candidates[candidatesCtr] = i;
                candidatesCtr++;
                visited[i] = 1;
            }
        }           

        for (i = 0; i < candidatesCtr - 1; i++) 
        {
            minIdx = i;
            for (j = i + 1; j < candidatesCtr; j++) 
            {
                if (strcmp(graph->vertices[candidates[j]], graph->vertices[candidates[minIdx]]) < 0) 
                {
                    minIdx = j;
                }
            }
            if (minIdx != i) 
            {
                temp = candidates[i];
                candidates[i] = candidates[minIdx];
                candidates[minIdx] = temp;
            }
        }

        for (i = 0; i < candidatesCtr; i++)
        {
            queue[tailofQueue] = candidates[i];
            tailofQueue++;
        }
    }
}

void DFS (graphType *graph, int previousIndex, String50 result[], int visited[], int* resultsCtr) 
{
    int i, minIdx, temp, j;
    int candidates[MAX_VERTICES];
    int candidateCtr = 0;
    
    visited[previousIndex] = 1;
    strcpy(result[*resultsCtr], graph->vertices[previousIndex]);
    (*resultsCtr)++;

    for (i = 0; i < graph->nVertices; i++) {
        if (graph->adjMatrix[previousIndex][i] && !visited[i]) {
            candidates[candidateCtr] = i;
            candidateCtr++; 
        }
    }

    for (i = 0; i < candidateCtr - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < candidateCtr; j++) 
        {
            if (strcmp(graph->vertices[candidates[j]], graph->vertices[candidates[minIdx]]) < 0) 
            {
                 minIdx = j;
            }
        }

        if (minIdx != i) {
            temp = candidates[i];
            candidates[i] = candidates[minIdx];
            candidates[minIdx] = temp;
        }
    }

    for (i = 0; i < candidateCtr; i++) {
        if (!visited[candidates[i]]) {
            DFS(graph, candidates[i], result, visited, resultsCtr);
        }
    }
}

void produceOutputFile5 (String50 baseName, graphType *graph, String50 start) 
{
    FILE *fp;
    String50 outputName;
    String50 result[MAX_VERTICES];
    int i;
    int startingIdx;

    strcpy(outputName, baseName);
    getOutputFileName(outputName,"-BFS");
    startingIdx = findVertexIdx(graph, start);

    fp = fopen(outputName,"w");

    if (fp == NULL)
    {
        printf("Error: Could not open output file\n");
    }
    else if (startingIdx == -1)
    {
        printf("Error: Starting vertex not found\n");
        fclose(fp);
    }
    else 
{
        BFS(graph, startingIdx, result);

        for (i = 0; i < graph->nVertices; i++) 
        {
            if (strlen(result[i]) > 0)
            {		
                fprintf(fp, "%s ", result[i]);
                if (i < graph->nVertices - 1 && strlen(result[i + 1]) > 0) 
                {
                    fprintf(fp, " ");
                }
            }
        }
        fprintf(fp,"\n");

        fclose(fp);
    }
}

void produceOutputFile6 (String50 baseName, graphType *graph, String50 start)
{
    FILE *fp;
    String50 outputName;
    String50 result[MAX_VERTICES];
    int i;
    int startingIdx;
    int nResultsCtr = 0;
    int nVisited[MAX_VERTICES];

    strcpy(outputName, baseName);
    getOutputFileName(outputName,"-DFS");
    startingIdx = findVertexIdx(graph, start);

    fp = fopen(outputName,"w");

    if (fp == NULL)
    {
        printf("Error: Could not open output file\n");
    }
    else if (startingIdx == -1)
    {
        printf("Error: Starting vertex not found\n");
        fclose(fp);
    }
    else
    {
        for (i = 0; i < MAX_VERTICES; i++)
        {
            nVisited[i] = 0;
        }

        DFS (graph, startingIdx, result, nVisited, &nResultsCtr);

        for (i = 0; i < nResultsCtr; i++)
        {
            fprintf(fp, "%s", result[i]);

            if (i < nResultsCtr - 1)
                fprintf(fp, " ");
        }

        fprintf(fp,"\n");
    }

    fclose (fp);
}
