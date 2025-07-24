#include <graph.h>

int produceOutputFile1(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int nSortedIndices[MAX_VERTICES];
    int i, j;
    int nEdgeCount;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-SET", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
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
        nSuccess = 1;
    }
    
    return nSuccess;
}

int produceOutputFile2(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int nSortedIndices[MAX_VERTICES];
    int i, j, nDegree;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-DEGREE", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
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
        nSuccess = 1;
    }
    
    return nSuccess;
}

int produceOutputFile3(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int i, j;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-LIST", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
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
        nSuccess = 1;
    }
    
    return nSuccess;
}

int produceOutputFile4(String10 strOutputFileName, graphType* pGraph)
{
    FILE* pFile;
    String50 strFileName;
    int i, j;
    int nSuccess;
    
    nSuccess = 0;
    createOutputFileName(strOutputFileName, "-MATRIX", strFileName);
    
    if ((pFile = fopen(strFileName, "w")) != NULL) {
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
        nSuccess = 1;
    }
    
    return nSuccess;
}


