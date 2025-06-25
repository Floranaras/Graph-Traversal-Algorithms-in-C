#include "graph.h"

void checkIsSubgraph(graphType* pGraphG, graphType* pGraphH, int* pIsSubgraph)
{
    int i, j;
    int nVertexFound;
    int nGIndex1, nGIndex2, nHIndex1, nHIndex2;
    int nAllVerticesFound, nAllEdgesFound;
    
    nAllVerticesFound = 1;
    nAllEdgesFound = 1;
    
    /* Check if all vertices of H exist in G */
    for (i = 0; i < pGraphH->nVertices && nAllVerticesFound == 1; i++) {
        nVertexFound = 0;
        for (j = 0; j < pGraphG->nVertices && nVertexFound == 0; j++) {
            if (strcmp(pGraphH->vertices[i], pGraphG->vertices[j]) == 0) {
                nVertexFound = 1;
            }
        }
        if (nVertexFound == 0) {
            nAllVerticesFound = 0;
        }
    }
    
    /* Check if all edges of H exist in G */
    if (nAllVerticesFound == 1) {
        for (nHIndex1 = 0; nHIndex1 < pGraphH->nVertices && nAllEdgesFound == 1; nHIndex1++) {
            for (nHIndex2 = 0; nHIndex2 < pGraphH->nVertices && nAllEdgesFound == 1; nHIndex2++) {
                if (pGraphH->adjMatrix[nHIndex1][nHIndex2] == 1) {
                    /* Find corresponding vertices in G */
                    nGIndex1 = findVertexIndex(pGraphG, pGraphH->vertices[nHIndex1]);
                    nGIndex2 = findVertexIndex(pGraphG, pGraphH->vertices[nHIndex2]);
                    
                    if (nGIndex1 == -1 || nGIndex2 == -1) {
                        nAllEdgesFound = 0;
                    } else {
                        if (pGraphG->adjMatrix[nGIndex1][nGIndex2] == 0) {
                            nAllEdgesFound = 0;
                        }
                    }
                }
            }
        }
    } else {
        nAllEdgesFound = 0;
    }
    
    if (nAllVerticesFound == 1 && nAllEdgesFound == 1) {
        *pIsSubgraph = 1;
    } else {
        *pIsSubgraph = 0;
    }
}

void produceSubgraphOutput(String10 strFileG, String10 strFileH, graphType* pGraphG, graphType* pGraphH)
{
    FILE* pFile;
    String50 strOutputFileName;
    String10 strBaseG, strBaseH;
    int nSortedIndices[MAX_VERTICES];
    int i, j;
    int nVertexFound, nEdgeFound;
    int nGIndex1, nGIndex2;
    int nIsSubgraph;
    int nIdx1, nIdx2;
    int nTemp;
    int nFoundDotG, nFoundDotH;
    
    /* Create base filenames */
    strcpy(strBaseG, strFileG);
    strcpy(strBaseH, strFileH);
    
    nFoundDotG = 0;
    for (i = 0; i < strlen(strBaseG) && nFoundDotG == 0; i++) {
        if (strBaseG[i] == '.') {
            strBaseG[i] = '\0';
            nFoundDotG = 1;
        }
    }
    
    nFoundDotH = 0;
    for (i = 0; i < strlen(strBaseH) && nFoundDotH == 0; i++) {
        if (strBaseH[i] == '.') {
            strBaseH[i] = '\0';
            nFoundDotH = 1;
        }
    }
    
    /* Create output filename: G-H-SUBGRAPH.TXT */
    strcpy(strOutputFileName, strBaseG);
    strcat(strOutputFileName, "-");
    strcat(strOutputFileName, strBaseH);
    strcat(strOutputFileName, "-SUBGRAPH.TXT");
    
    if ((pFile = fopen(strOutputFileName, "w")) != NULL) {
        /* Sort vertices of H alphabetically */
        for (i = 0; i < pGraphH->nVertices; i++) {
            nSortedIndices[i] = i;
        }
        
        for (i = 0; i < pGraphH->nVertices - 1; i++) {
            for (j = 0; j < pGraphH->nVertices - 1 - i; j++) {
                if (compareStrings(pGraphH->vertices[nSortedIndices[j]], pGraphH->vertices[nSortedIndices[j + 1]]) > 0) {
                    nTemp = nSortedIndices[j];
                    nSortedIndices[j] = nSortedIndices[j + 1];
                    nSortedIndices[j + 1] = nTemp;
                }
            }
        }
        
        /* Write vertices with + or - */
        for (i = 0; i < pGraphH->nVertices; i++) {
            nVertexFound = findVertexIndex(pGraphG, pGraphH->vertices[nSortedIndices[i]]);
            if (nVertexFound != -1) {
                fprintf(pFile, "%s +\n", pGraphH->vertices[nSortedIndices[i]]);
            } else {
                fprintf(pFile, "%s -\n", pGraphH->vertices[nSortedIndices[i]]);
            }
        }
        
        /* Write edges with + or - in alphabetical order */
        for (i = 0; i < pGraphH->nVertices; i++) {
            for (j = i + 1; j < pGraphH->nVertices; j++) {
                nIdx1 = nSortedIndices[i];
                nIdx2 = nSortedIndices[j];
                
                if (pGraphH->adjMatrix[nIdx1][nIdx2] == 1) {
                    /* Check if this edge exists in G */
                    nGIndex1 = findVertexIndex(pGraphG, pGraphH->vertices[nIdx1]);
                    nGIndex2 = findVertexIndex(pGraphG, pGraphH->vertices[nIdx2]);
                    
                    nEdgeFound = 0;
                    if (nGIndex1 != -1 && nGIndex2 != -1) {
                        if (pGraphG->adjMatrix[nGIndex1][nGIndex2] == 1) {
                            nEdgeFound = 1;
                        }
                    }
                    
                    if (nEdgeFound == 1) {
                        fprintf(pFile, "(%s,%s) +\n", pGraphH->vertices[nIdx1], pGraphH->vertices[nIdx2]);
                    } else {
                        fprintf(pFile, "(%s,%s) -\n", pGraphH->vertices[nIdx1], pGraphH->vertices[nIdx2]);
                    }
                }
            }
        }
        
        /* Check if H is subgraph of G and write conclusion */
        checkIsSubgraph(pGraphG, pGraphH, &nIsSubgraph);
        if (nIsSubgraph == 1) {
            fprintf(pFile, "%s is a subgraph of %s.\n", strBaseH, strBaseG);
        } else {
            fprintf(pFile, "%s is a NOT subgraph of %s.\n", strBaseH, strBaseG);
        }
        
        fclose(pFile);
    }
}

int main()
{
    graphType graphG, graphH;
    String10 strFileG, strFileH;
    int nFileSuccessG, nFileSuccessH;
    int nCanProceed;
    
    nCanProceed = 1;
    
    /* Get first graph filename */
    printf("Input first graph filename: ");
    scanf("%s", strFileG);
    
    /* Get second graph filename */
    printf("Input second graph filename: ");
    scanf("%s", strFileH);
    
    /* Read both files */
    nFileSuccessG = readInputFile(strFileG, &graphG);
    if (nFileSuccessG == 0) {
        printf("File %s not found.\n", strFileG);
        nCanProceed = 0;
    }
    
    if (nCanProceed == 1) {
        nFileSuccessH = readInputFile(strFileH, &graphH);
        if (nFileSuccessH == 0) {
            printf("File %s not found.\n", strFileH);
            nCanProceed = 0;
        }
    }
    
    if (nCanProceed == 1) {
        /* Produce subgraph output */
        produceSubgraphOutput(strFileG, strFileH, &graphG, &graphH);
    }
    
    return 0;
}