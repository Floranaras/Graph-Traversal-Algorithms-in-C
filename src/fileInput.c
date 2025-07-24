#include <head.h>
#include <fileInput.h>

int readInputFile(String10 strInputFileName, graphType* pGraph)
{
    FILE* pFile;
    int i, j;
    String10 strToken;
    int nSuccess;
    
    nSuccess = 0;
    
    if ((pFile = fopen(strInputFileName, "r")) != NULL) {
        /* Read number of vertices */
        fscanf(pFile, "%d", &pGraph->nVertices);
        
        /* Initialize adjacency matrix and lists */
        for (i = 0; i < MAX_VERTICES; i++) {
            pGraph->adjCount[i] = 0;
            for (j = 0; j < MAX_VERTICES; j++) {
                pGraph->adjMatrix[i][j] = 0;
            }
        }
        
        /* Read adjacency information */
        for (i = 0; i < pGraph->nVertices; i++) {
            /* Read vertex name */
            fscanf(pFile, "%s", pGraph->vertices[i]);
            
            /* Read adjacent vertices until -1 */
            pGraph->adjCount[i] = 0;
            fscanf(pFile, "%s", strToken);
            while (strcmp(strToken, "-1") != 0) {
                strcpy(pGraph->adjList[i][pGraph->adjCount[i]], strToken);
                pGraph->adjCount[i]++;
                fscanf(pFile, "%s", strToken);
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
        nSuccess = 1;
    }
    
    return nSuccess;
}

int findVertexIndex(graphType* pGraph, String10 strVertex)
{
    int i;
    int nFoundIndex;
    
    nFoundIndex = -1;
    
    for (i = 0; i < pGraph->nVertices; i++) {
        if (strcmp(pGraph->vertices[i], strVertex) == 0) {
            nFoundIndex = i;
            i = pGraph->nVertices; /* Exit loop naturally */
        }
    }
    
    return nFoundIndex;
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
            i = strlen(strOutputFileName); /* Exit loop naturally */
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
