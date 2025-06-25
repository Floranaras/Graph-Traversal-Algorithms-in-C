/* 01-BONUS.c - Subgraph checking program */
#include <graph.h>

int isSubgraph(graphType* pGraphG, graphType* pGraphH)
{
    int i, j;
    int nVertexFound;
    int nGIndex1, nGIndex2, nHIndex1, nHIndex2;
    
    /* Check if all vertices of H exist in G */
    for (i = 0; i < pGraphH->nVertices; i++) {
        nVertexFound = 0;
        for (j = 0; j < pGraphG->nVertices; j++) {
            if (strcmp(pGraphH->vertices[i], pGraphG->vertices[j]) == 0) {
                nVertexFound = 1;
                break;
            }
        }
        if (nVertexFound == 0) {
            return 0; /* Vertex not found in G */
        }
    }
    
    /* Check if all edges of H exist in G */
    for (nHIndex1 = 0; nHIndex1 < pGraphH->nVertices; nHIndex1++) {
        for (nHIndex2 = 0; nHIndex2 < pGraphH->nVertices; nHIndex2++) {
            if (pGraphH->adjMatrix[nHIndex1][nHIndex2] == 1) {
                /* Find corresponding vertices in G */
                nGIndex1 = findVertexIndex(pGraphG, pGraphH->vertices[nHIndex1]);
                nGIndex2 = findVertexIndex(pGraphG, pGraphH->vertices[nHIndex2]);
                
                if (nGIndex1 == -1 || nGIndex2 == -1) {
                    return 0; /* Vertex not found */
                }
                
                if (pGraphG->adjMatrix[nGIndex1][nGIndex2] == 0) {
                    return 0; /* Edge not found in G */
                }
            }
        }
    }
    
    return 1; /* H is a subgraph of G */
}

int produceSubgraphOutput(String10 strFileG, String10 strFileH, graphType* pGraphG, graphType* pGraphH)
{
    FILE* pFile;
    String50 strOutputFileName;
    String10 strBaseG, strBaseH;
    int nSortedIndices[MAX_VERTICES];
    int i, j;
    int nVertexFound, nEdgeFound;
    int nGIndex1, nGIndex2;
    int nIsSubgraph;
    
    /* Create base filenames */
    strcpy(strBaseG, strFileG);
    strcpy(strBaseH, strFileH);
    for (i = 0; i < strlen(strBaseG); i++) {
        if (strBaseG[i] == '.') {
            strBaseG[i] = '\0';
            break;
        }
    }
    for (i = 0; i < strlen(strBaseH); i++) {
        if (strBaseH[i] == '.') {
            strBaseH[i] = '\0';
            break;
        }
    }
    
    /* Create output filename: G-H-SUBGRAPH.TXT */
    strcpy(strOutputFileName, strBaseG);
    strcat(strOutputFileName, "-");
    strcat(strOutputFileName, strBaseH);
    strcat(strOutputFileName, "-SUBGRAPH.TXT");
    
    pFile = fopen(strOutputFileName, "w");
    if (pFile == NULL) {
        return 0;
    }
    
    /* Sort vertices of H alphabetically */
    for (i = 0; i < pGraphH->nVertices; i++) {
        nSortedIndices[i] = i;
    }
    
    for (i = 0; i < pGraphH->nVertices - 1; i++) {
        for (j = 0; j < pGraphH->nVertices - 1 - i; j++) {
            if (compareStrings(pGraphH->vertices[nSortedIndices[j]], pGraphH->vertices[nSortedIndices[j + 1]]) > 0) {
                int nTemp = nSortedIndices[j];
                nSortedIndices[j] = nSortedIndices[j + 1];
                nSortedIndices[j + 1] = nTemp;
            }
        }
    }
    
    /* Write vertices with + or - */
    for (i = 0; i < pGraphH->nVertices; i++) {
        nVertexFound = (findVertexIndex(pGraphG, pGraphH->vertices[nSortedIndices[i]]) != -1) ? 1 : 0;
        fprintf(pFile, "%s %c\n", pGraphH->vertices[nSortedIndices[i]], nVertexFound ? '+' : '-');
    }
    
    /* Write edges with + or - in alphabetical order */
    for (i = 0; i < pGraphH->nVertices; i++) {
        for (j = i + 1; j < pGraphH->nVertices; j++) {
            int nIdx1 = nSortedIndices[i];
            int nIdx2 = nSortedIndices[j];
            
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
                
                fprintf(pFile, "(%s,%s) %c\n", 
                    pGraphH->vertices[nIdx1], 
                    pGraphH->vertices[nIdx2], 
                    nEdgeFound ? '+' : '-');
            }
        }
    }
    
    /* Check if H is subgraph of G and write conclusion */
    nIsSubgraph = isSubgraph(pGraphG, pGraphH);
    fprintf(pFile, "%s is %ssubgraph of %s.\n", 
        strBaseH, 
        nIsSubgraph ? "a " : "a NOT ", 
        strBaseG);
    
    fclose(pFile);
    return 1;
}

int main()
{
    graphType graphG, graphH;
    String10 strFileG, strFileH;
    int nFileExists;
    
    /* Get first graph filename */
    printf("Input first graph filename: ");
    scanf("%s", strFileG);
    
    /* Get second graph filename */
    printf("Input second graph filename: ");
    scanf("%s", strFileH);
    
    /* Read both files */
    nFileExists = readInputFile(strFileG, &graphG);
    if (nFileExists == 0) {
        printf("File %s not found.\n", strFileG);
        return 0;
    }
    
    nFileExists = readInputFile(strFileH, &graphH);
    if (nFileExists == 0) {
        printf("File %s not found.\n", strFileH);
        return 0;
    }
    
    /* Produce subgraph output */
    produceSubgraphOutput(strFileG, strFileH, &graphG, &graphH);
    
    return 0;
}