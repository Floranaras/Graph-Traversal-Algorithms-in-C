/* graph.c */
#include "graph.h"

int readInputFile(String10 strInputFileName, graphType* pGraph)
{
    FILE* pFile;
    int i, j;
    char strLine[256];
    char* pToken;
    
    pFile = fopen(strInputFileName, "r");
    if (pFile == NULL) {
        return 0; /* File not found */
    }
    
    /* Read number of vertices */
    fscanf(pFile, "%d", &pGraph->nVertices);
    
    /* Initialize adjacency matrix and lists */
    for (i = 0; i < MAX_VERTICES; i++) {
        pGraph->adjCount[i] = 0;
        for (j = 0; j < MAX_VERTICES; j++) {
            pGraph->adjMatrix[i][j] = 0;
        }
    }
    
    /* Clear the newline after the number */
    fgets(strLine, sizeof(strLine), pFile);
    
    /* Read adjacency information */
    for (i = 0; i < pGraph->nVertices; i++) {
        fgets(strLine, sizeof(strLine), pFile);
        
        /* Get the first token (vertex name) */
        pToken = strtok(strLine, " \t\n");
        if (pToken != NULL) {
            strcpy(pGraph->vertices[i], pToken);
            
            /* Store adjacent vertices in input order */
            pGraph->adjCount[i] = 0;
            pToken = strtok(NULL, " \t\n");
            while (pToken != NULL && strcmp(pToken, "-1") != 0) {
                strcpy(pGraph->adjList[i][pGraph->adjCount[i]], pToken);
                pGraph->adjCount[i]++;
                pToken = strtok(NULL, " \t\n");
            }
        }
    }
    
    /* Now build adjacency matrix */
    for (i = 0; i < pGraph->nVertices; i++) {
        for (j = 0; j < pGraph->adjCount[i]; j++) {
            int nAdjIndex = findVertexIndex(pGraph, pGraph->adjList[i][j]);
            if (nAdjIndex != -1) {
                pGraph->adjMatrix[i][nAdjIndex] = 1;
                pGraph->adjMatrix[nAdjIndex][i] = 1; /* Undirected graph */
            }
        }
    }
    
    fclose(pFile);
    return 1; /* Success */
}

int findVertexIndex(graphType* pGraph, String10 strVertex)
{
    int i;
    
    for (i = 0; i < pGraph->nVertices; i++) {
        if (strcmp(pGraph->vertices[i], strVertex) == 0) {
            return i;
        }
    }
    return -1; /* Not found */
}

int createOutputFileName(String10 strInputFileName, char* strSuffix, String50 strOutputFileName)
{
    int i;
    
    /* Copy input filename without extension */
    strcpy(strOutputFileName, strInputFileName);
    
    /* Remove .TXT extension */
    for (i = 0; i < strlen(strOutputFileName); i++) {
        if (strOutputFileName[i] == '.') {
            strOutputFileName[i] = '\0';
            break;
        }
    }
    
    /* Add suffix and extension */
    strcat(strOutputFileName, strSuffix);
    strcat(strOutputFileName, ".TXT");
    
    return 1;
}

int compareStrings(String10 str1, String10 str2)
{
    return strcmp(str1, str2);
}

int sortVerticesAlphabetically(graphType* pGraph, int nIndices[])
{
    int i, j, nTemp;
    
    /* Initialize indices array */
    for (i = 0; i < pGraph->nVertices; i++) {
        nIndices[i] = i;
    }
    
    /* Simple bubble sort */
    for (i = 0; i < pGraph->nVertices - 1; i++) {
        for (j = 0; j < pGraph->nVertices - 1 - i; j++) {
            if (compareStrings(pGraph->vertices[nIndices[j]], pGraph->vertices[nIndices[j + 1]]) > 0) {
                nTemp = nIndices[j];
                nIndices[j] = nIndices[j + 1];
                nIndices[j + 1] = nTemp;
            }
        }
    }
    
    return 1;
}

int produceOutputFile1(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int nSortedIndices[MAX_VERTICES];
    int i, j;
    int nEdgeCount;
    
    createOutputFileName(strOutputFileName, "-SET", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    /* Sort vertices alphabetically */
    sortVerticesAlphabetically(pGraph, nSortedIndices);
    
    /* Write V(G) */
    fprintf(pFile, "V(G)={");
    for (i = 0; i < pGraph->nVertices; i++) {
        fprintf(pFile, "%s", pGraph->vertices[nSortedIndices[i]]);
        if (i < pGraph->nVertices - 1) {
            fprintf(pFile, ",");
        }
    }
    fprintf(pFile, "}\n");
    
    /* Write E(G) */
    fprintf(pFile, "E(G)={");
    nEdgeCount = 0;
    for (i = 0; i < pGraph->nVertices; i++) {
        for (j = i + 1; j < pGraph->nVertices; j++) {
            if (pGraph->adjMatrix[nSortedIndices[i]][nSortedIndices[j]] == 1) {
                if (nEdgeCount > 0) {
                    fprintf(pFile, ",");
                }
                fprintf(pFile, "(%s,%s)", pGraph->vertices[nSortedIndices[i]], pGraph->vertices[nSortedIndices[j]]);
                nEdgeCount++;
            }
        }
    }
    fprintf(pFile, "}\n");
    
    fclose(pFile);
    return 1;
}

int produceOutputFile2(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int nSortedIndices[MAX_VERTICES];
    int i, j, nDegree;
    
    createOutputFileName(strOutputFileName, "-DEGREE", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    /* Sort vertices alphabetically */
    sortVerticesAlphabetically(pGraph, nSortedIndices);
    
    /* Write vertices with degrees */
    for (i = 0; i < pGraph->nVertices; i++) {
        nDegree = 0;
        for (j = 0; j < pGraph->nVertices; j++) {
            if (pGraph->adjMatrix[nSortedIndices[i]][j] == 1) {
                nDegree++;
            }
        }
        fprintf(pFile, "%s %d\n", pGraph->vertices[nSortedIndices[i]], nDegree);
    }
    
    fclose(pFile);
    return 1;
}

int produceOutputFile3(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int i, j;
    
    createOutputFileName(strOutputFileName, "-LIST", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    /* Write adjacency list in same order as input file */
    for (i = 0; i < pGraph->nVertices; i++) {
        fprintf(pFile, "%s", pGraph->vertices[i]);
        /* Use stored adjacency list to maintain input order */
        for (j = 0; j < pGraph->adjCount[i]; j++) {
            fprintf(pFile, "->%s", pGraph->adjList[i][j]);
        }
        fprintf(pFile, "->\\\n");
    }
    
    fclose(pFile);
    return 1;
}

int produceOutputFile4(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int i, j;
    
    createOutputFileName(strOutputFileName, "-MATRIX", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    /* Write column headers */
    fprintf(pFile, " ");
    for (i = 0; i < pGraph->nVertices; i++) {
        fprintf(pFile, " %s", pGraph->vertices[i]);
    }
    fprintf(pFile, "\n");
    
    /* Write matrix with row labels */
    for (i = 0; i < pGraph->nVertices; i++) {
        fprintf(pFile, "%s", pGraph->vertices[i]);
        for (j = 0; j < pGraph->nVertices; j++) {
            fprintf(pFile, " %d", pGraph->adjMatrix[i][j]);
        }
        fprintf(pFile, "\n");
    }
    
    fclose(pFile);
    return 1;
}

int bfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[])
{
    int nQueue[MAX_VERTICES];
    int nFront, nRear;
    int nVisited[MAX_VERTICES];
    int nResultCount;
    int i, nCurrentVertex;
    int nCandidates[MAX_VERTICES];
    int nCandidateCount, j, nMinIndex, nTemp;
    
    /* Initialize */
    nFront = 0;
    nRear = 0;
    nResultCount = 0;
    
    for (i = 0; i < pGraph->nVertices; i++) {
        nVisited[i] = 0;
    }
    
    /* Start BFS */
    nQueue[nRear] = nStartIndex;
    nRear++;
    nVisited[nStartIndex] = 1;
    
    while (nFront < nRear) {
        nCurrentVertex = nQueue[nFront];
        nFront++;
        
        strcpy(strResult[nResultCount], pGraph->vertices[nCurrentVertex]);
        nResultCount++;
        
        /* Find all unvisited adjacent vertices */
        nCandidateCount = 0;
        for (i = 0; i < pGraph->nVertices; i++) {
            if (pGraph->adjMatrix[nCurrentVertex][i] == 1 && nVisited[i] == 0) {
                nCandidates[nCandidateCount] = i;
                nCandidateCount++;
                nVisited[i] = 1;
            }
        }
        
        /* Sort candidates alphabetically */
        for (i = 0; i < nCandidateCount - 1; i++) {
            nMinIndex = i;
            for (j = i + 1; j < nCandidateCount; j++) {
                if (compareStrings(pGraph->vertices[nCandidates[j]], pGraph->vertices[nCandidates[nMinIndex]]) < 0) {
                    nMinIndex = j;
                }
            }
            if (nMinIndex != i) {
                nTemp = nCandidates[i];
                nCandidates[i] = nCandidates[nMinIndex];
                nCandidates[nMinIndex] = nTemp;
            }
        }
        
        /* Add sorted candidates to queue */
        for (i = 0; i < nCandidateCount; i++) {
            nQueue[nRear] = nCandidates[i];
            nRear++;
        }
    }
    
    return nResultCount;
}

int dfsTraversalRecursive(graphType* pGraph, int nCurrentVertex, int nVisited[], String10 strResult[], int* pResultCount)
{
    int i, j;
    int nCandidates[MAX_VERTICES];
    int nCandidateCount, nMinIndex, nTemp;
    
    nVisited[nCurrentVertex] = 1;
    strcpy(strResult[*pResultCount], pGraph->vertices[nCurrentVertex]);
    (*pResultCount)++;
    
    /* Find all unvisited adjacent vertices */
    nCandidateCount = 0;
    for (i = 0; i < pGraph->nVertices; i++) {
        if (pGraph->adjMatrix[nCurrentVertex][i] == 1 && nVisited[i] == 0) {
            nCandidates[nCandidateCount] = i;
            nCandidateCount++;
        }
    }
    
    /* Sort candidates alphabetically */
    for (i = 0; i < nCandidateCount - 1; i++) {
        nMinIndex = i;
        for (j = i + 1; j < nCandidateCount; j++) {
            if (compareStrings(pGraph->vertices[nCandidates[j]], pGraph->vertices[nCandidates[nMinIndex]]) < 0) {
                nMinIndex = j;
            }
        }
        if (nMinIndex != i) {
            nTemp = nCandidates[i];
            nCandidates[i] = nCandidates[nMinIndex];
            nCandidates[nMinIndex] = nTemp;
        }
    }
    
    /* Visit candidates in alphabetical order */
    for (i = 0; i < nCandidateCount; i++) {
        if (nVisited[nCandidates[i]] == 0) {
            dfsTraversalRecursive(pGraph, nCandidates[i], nVisited, strResult, pResultCount);
        }
    }
    
    return 1;
}

int dfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[])
{
    int nVisited[MAX_VERTICES];
    int nResultCount;
    int i;
    
    /* Initialize */
    nResultCount = 0;
    for (i = 0; i < pGraph->nVertices; i++) {
        nVisited[i] = 0;
    }
    
    /* Start DFS */
    dfsTraversalRecursive(pGraph, nStartIndex, nVisited, strResult, &nResultCount);
    
    return nResultCount;
}

int produceOutputFile5(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex)
{
    FILE* pFile;
    String50 strFileName;
    String10 strResult[MAX_VERTICES];
    int nStartIndex, nResultCount, i;
    
    createOutputFileName(strOutputFileName, "-BFS", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    nStartIndex = findVertexIndex(pGraph, strStartVertex);
    if (nStartIndex == -1) {
        fclose(pFile);
        return 0;
    }
    
    nResultCount = bfsTraversal(pGraph, nStartIndex, strResult);
    
    for (i = 0; i < nResultCount; i++) {
        fprintf(pFile, "%s", strResult[i]);
        if (i < nResultCount - 1) {
            fprintf(pFile, " ");
        }
    }
    fprintf(pFile, "\n");
    
    fclose(pFile);
    return 1;
}

int produceOutputFile6(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex)
{
    FILE* pFile;
    String50 strFileName;
    String10 strResult[MAX_VERTICES];
    int nStartIndex, nResultCount, i;
    
    createOutputFileName(strOutputFileName, "-DFS", strFileName);
    pFile = fopen(strFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    nStartIndex = findVertexIndex(pGraph, strStartVertex);
    if (nStartIndex == -1) {
        fclose(pFile);
        return 0;
    }
    
    nResultCount = dfsTraversal(pGraph, nStartIndex, strResult);
    
    for (i = 0; i < nResultCount; i++) {
        fprintf(pFile, "%s", strResult[i]);
        if (i < nResultCount - 1) {
            fprintf(pFile, " ");
        }
    }
    fprintf(pFile, "\n");
    
    fclose(pFile);
    return 1;
}