#include <transversal.h>

int performBfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[])
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

int performDfsRecursive(graphType* pGraph, int nCurrentVertex, int nVisited[], String10 strResult[], int* pResultCount)
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
            performDfsRecursive(pGraph, nCandidates[i], nVisited, strResult, pResultCount);
        }
    }
    
    return 1;
}

int performDfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[])
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
    performDfsRecursive(pGraph, nStartIndex, nVisited, strResult, &nResultCount);
    
    return nResultCount;
}

int produceOutputFile5(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex)
{
    FILE* pFile;
    String50 strFileName;
    String10 strResult[MAX_VERTICES];
    int nStartIndex, nResultCount, i;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-BFS", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
        nStartIndex = findVertexIndex(pGraph, strStartVertex);
        if (nStartIndex != -1) {
            nResultCount = performBfsTraversal(pGraph, nStartIndex, strResult);
            
            for (i = 0; i < nResultCount; i++) {
                fprintf(pFile, "%s", strResult[i]);
                if (i < nResultCount - 1) {
                    fprintf(pFile, " ");
                }
            }
            fprintf(pFile, "\n");
            nSuccess = 1;
        }
        fclose(pFile);
    }
    
    return nSuccess;
}

int produceOutputFile6(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex)
{
    FILE* pFile;
    String50 strFileName;
    String10 strResult[MAX_VERTICES];
    int nStartIndex, nResultCount, i;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-DFS", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
        nStartIndex = findVertexIndex(pGraph, strStartVertex);
        if (nStartIndex != -1) {
            nResultCount = performDfsTraversal(pGraph, nStartIndex, strResult);
            
            for (i = 0; i < nResultCount; i++) {
                fprintf(pFile, "%s", strResult[i]);
                if (i < nResultCount - 1) {
                    fprintf(pFile, " ");
                }
            }
            fprintf(pFile, "\n");
            nSuccess = 1;
        }
        fclose(pFile);
    }
    
    return nSuccess;
}
