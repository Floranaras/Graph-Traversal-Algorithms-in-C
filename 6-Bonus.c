#include "graph.c"

void removeFileExtension(String50 fileName)
{
    int i = 0;
    while (i < strlen(fileName) && fileName[i] != '.')
        i++;
    
    if (i < strlen(fileName))
        fileName[i] = '\0';
}

void createOutputFileName(String50 outputName, String50 baseG, String50 baseH)
{
    strcpy(outputName, baseG);
    strcat(outputName, "-");
    strcat(outputName, baseH);
    strcat(outputName, "-SUBGRAPH.TXT");
}

void sortVerticesAlphabetically(graphType* graph, int* sortedIndices)
{
    int i, j, temp;
    
    for (i = 0; i < graph->nVertices; i++)
        sortedIndices[i] = i;
    
    for (i = 0; i < graph->nVertices - 1; i++)
    {
        for (j = 0; j < graph->nVertices - 1 - i; j++)
        {
            if (strcmp(graph->vertices[sortedIndices[j]], graph->vertices[sortedIndices[j + 1]]) > 0)
            {
                temp = sortedIndices[j];
                sortedIndices[j] = sortedIndices[j + 1];
                sortedIndices[j + 1] = temp;
            }
        }
    }
}

void writeVerticesStatus(FILE* file, graphType* graphG, graphType* graphH, int* sortedIndices)
{
    int i, vertexFound;
    
    for (i = 0; i < graphH->nVertices; i++)
    {
        vertexFound = findVertexIdx(graphG, graphH->vertices[sortedIndices[i]]);
        
        if (vertexFound != -1)
            fprintf(file, "%s +\n", graphH->vertices[sortedIndices[i]]);
        else
            fprintf(file, "%s -\n", graphH->vertices[sortedIndices[i]]);
    }
}

void writeEdgesStatus(FILE* file, graphType* graphG, graphType* graphH, int* sortedIndices)
{
    int i, j, idx1, idx2, gIndex1, gIndex2, edgeFound;
    
    for (i = 0; i < graphH->nVertices; i++)
    {
        for (j = i + 1; j < graphH->nVertices; j++)
        {
            idx1 = sortedIndices[i];
            idx2 = sortedIndices[j];
            
            if (graphH->adjMatrix[idx1][idx2] == 1)
            {
                gIndex1 = findVertexIdx(graphG, graphH->vertices[idx1]);
                gIndex2 = findVertexIdx(graphG, graphH->vertices[idx2]);
                
                edgeFound = 0;
                if (gIndex1 != -1 && gIndex2 != -1)
                {
                    if (graphG->adjMatrix[gIndex1][gIndex2] == 1)
                    {
                        edgeFound = 1;
                    }
                }
                
                if (edgeFound)
                {
                    fprintf(file, "(%s,%s) +\n", graphH->vertices[idx1], graphH->vertices[idx2]);
                }
                else
                {
                    fprintf(file, "(%s,%s) -\n", graphH->vertices[idx1], graphH->vertices[idx2]);
                }
            }
        }
    }
}

int allVerticesExist(graphType* pGraphG, graphType* pGraphH)
{
    int i, j, nVertexFound;
    
    for (i = 0; i < pGraphH->nVertices; i++) 
    {
        nVertexFound = 0;
        for (j = 0; j < pGraphG->nVertices && nVertexFound == 0; j++) 
        {
            if (strcmp(pGraphH->vertices[i], pGraphG->vertices[j]) == 0)
                nVertexFound = 1;
        }
        if (nVertexFound == 0)
            return 0;
    }
    return 1;
}

int allEdgesExist(graphType* pGraphG, graphType* pGraphH)
{
    int nHIndex1, nHIndex2, nGIndex1, nGIndex2;
    
    for (nHIndex1 = 0; nHIndex1 < pGraphH->nVertices; nHIndex1++) 
    {
        for (nHIndex2 = 0; nHIndex2 < pGraphH->nVertices; nHIndex2++) 
        {
            if (pGraphH->adjMatrix[nHIndex1][nHIndex2] == 1)
            {
                nGIndex1 = findVertexIdx(pGraphG, pGraphH->vertices[nHIndex1]);
                nGIndex2 = findVertexIdx(pGraphG, pGraphH->vertices[nHIndex2]);
                
                if (nGIndex1 == -1 || nGIndex2 == -1)
                    return 0;
                if (pGraphG->adjMatrix[nGIndex1][nGIndex2] == 0) 
                    return 0;
            }
        }
    }
    return 1;
}

void checkIsSubgraph(graphType* pGraphG, graphType* pGraphH, int* pIsSubgraph)
{
    int nAllVerticesFound, nAllEdgesFound;
    
    nAllVerticesFound = allVerticesExist(pGraphG, pGraphH);
    
    if (nAllVerticesFound == 1)
        nAllEdgesFound = allEdgesExist(pGraphG, pGraphH);
    else
        nAllEdgesFound = 0;
    
    if (nAllVerticesFound == 1 && nAllEdgesFound == 1)
        *pIsSubgraph = 1;
    else
        *pIsSubgraph = 0;
}

void writeSubgraphConclusion(FILE* pFile, String50 strBaseG, String50 strBaseH, int nIsSubgraph)
{
    if (nIsSubgraph == 1)
    {
        fprintf(pFile, "%s is a subgraph of %s.\n", strBaseH, strBaseG);
    }
    else
    {
        fprintf(pFile, "%s is a not subgraph of %s.\n", strBaseH, strBaseG);
    }
}

void produceSubgraphOutput(String50 strFileG, String50 strFileH, graphType* pGraphG, graphType* pGraphH)
{
    FILE* pFile;
    String50 strOutputFileName;
    String50 strBaseG, strBaseH;
    int nSortedIndices[MAX_VERTICES];
    int nIsSubgraph;
    
    strcpy(strBaseG, strFileG);
    strcpy(strBaseH, strFileH);
    
    removeFileExtension(strBaseG);
    removeFileExtension(strBaseH);
    createOutputFileName(strOutputFileName, strBaseG, strBaseH);
    
    pFile = fopen(strOutputFileName, "w");
    if (pFile != NULL)
    {
        sortVerticesAlphabetically(pGraphH, nSortedIndices);
        writeVerticesStatus(pFile, pGraphG, pGraphH, nSortedIndices);
        writeEdgesStatus(pFile, pGraphG, pGraphH, nSortedIndices);
        
        checkIsSubgraph(pGraphG, pGraphH, &nIsSubgraph);
        writeSubgraphConclusion(pFile, strBaseG, strBaseH, nIsSubgraph);
        
        fclose(pFile);
    }
}

int readBothGraphFiles(String50 strFileG, String50 strFileH, graphType* graphG, graphType* graphH)
{
    int nFileSuccessG, nFileSuccessH;
    
    nFileSuccessG = readInputFile(strFileG, graphG);
    if (!nFileSuccessG) 
    {
        printf("File %s not found.\n", strFileG);
        return 0;
    }
    
    nFileSuccessH = readInputFile(strFileH, graphH);
    if (!nFileSuccessH) 
    {
        printf("File %s not found.\n", strFileH);
        return 0;
    }
    
    return 1;
}

void getInputFilenames(String50 strFileG, String50 strFileH)
{
    printf("Input first graph filename: ");
    scanf("%s", strFileG);
    
    printf("Input second graph filename: ");
    scanf("%s", strFileH);
}

int main()
{
    graphType graphG, graphH;
    String50 strFileG, strFileH;
    int nCanProceed;
    
    getInputFilenames(strFileG, strFileH);
    
    nCanProceed = readBothGraphFiles(strFileG, strFileH, &graphG, &graphH);
    if (nCanProceed == 1)
    {
        produceSubgraphOutput(strFileG, strFileH, &graphG, &graphH);
        
        freeAdjList(&graphG);
        freeAdjList(&graphH);
    }
    
    return 0;
}