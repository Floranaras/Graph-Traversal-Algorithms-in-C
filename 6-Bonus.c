/*
@file 6-BONUS.c
@Driver file for subgraph determinination
@author RANARA, Ramil Carlos, SIA, Justin Michael, TIU, Avram Nathaniel -
Programmer
@date 7/22/2025
@version 1.0
*/

#include "graph.c"

/*
                Purpose: To remove the file extension from a file's name
                Returns: void
                @param fileName The file name with a file extension
                Pre-condition:
                - A string of length 50 or less must be provided
                Post-condition:
                - File extension is removed from the file name
*/
void removeFileExtension(String50 fileName) {
  int i = 0;
  while (i < strlen(fileName) && fileName[i] != '.')
    i++;

  if (i < strlen(fileName))
    fileName[i] = '\0';
}

/*
                Purpose: To create the name of the output file with a file
   extension Returns: void
                @param outputName The file name with the file extension
                @param baseG The file name of the first graph
                @param baseH The file name of the second graph
                Pre-condition:
                - outputName, baseG, and baseH must be nonempty and have a
   length of 50 or less Post-condition:
                - outputName contains the file name of the output file with file
   extension
*/
void createOutputFileName(String50 outputName, String50 baseG, String50 baseH) {
  strcpy(outputName, baseG);
  strcat(outputName, "-");
  strcat(outputName, baseH);
  strcat(outputName, "-SUBGRAPH.TXT");
}

/*
                Purpose: To sort an array of integers that correspond to the
   indices of a graph's vertices Returns: void
                @param graph The pointer to a graph structure
                @param sortedIndices The pointer to an integer array
                Pre-condition:
                - graph must be initialized prior to calling this function
                Post-condition:
                - sortedIndices contains the sorted array of indices
*/
void sortVerticesAlphabetically(graphType *graph, int *sortedIndices) {
  int i, j, temp;

  for (i = 0; i < graph->nVertices; i++)
    sortedIndices[i] = i;

  for (i = 0; i < graph->nVertices - 1; i++) {
    for (j = 0; j < graph->nVertices - 1 - i; j++) {
      if (strcmp(graph->vertices[sortedIndices[j]],
                 graph->vertices[sortedIndices[j + 1]]) > 0) {
        temp = sortedIndices[j];
        sortedIndices[j] = sortedIndices[j + 1];
        sortedIndices[j + 1] = temp;
      }
    }
  }
}

/*
                Purpose: To write on a file if a vertex in the second graph
   exists in the first graph or not Returns: void
                @param File The pointer to a file
                @param graphG The pointer to the first graph
                @param graphH The pointer to the second graph
                @param sortedIndices The pointer to an integer array
                Pre-condition:
                - sortedIndices must be sorted prior to calling this function
                - graphG and graphH must be initialized prior to calling this
   function Post-condition:
                - file will be updated with the vertices of the second graph
                  and their statuses of being included in the first graph
*/
void writeVerticesStatus(FILE *file, graphType *graphG, graphType *graphH,
                         int *sortedIndices) {
  int i, vertexFound;

  for (i = 0; i < graphH->nVertices; i++) {
    vertexFound = findVertexIdx(graphG, graphH->vertices[sortedIndices[i]]);

    if (vertexFound != -1)
      fprintf(file, "%s +\n", graphH->vertices[sortedIndices[i]]);

    else
      fprintf(file, "%s -\n", graphH->vertices[sortedIndices[i]]);
  }
}

/*
                Purpose: Checks if an edge exists in graph G and returns the
   appropriate status symbol Returns: '+' if edge exists in graph G, '-'
   otherwise
                @param graphG The pointer to the first graph
                @param graphH The pointer to the second graph
                @param idx1 The first vertex index in graph H
                @param idx2 The second vertex index in graph H
                Pre-condition:
                - graphG and graphH must be initialized prior to calling this
   function
                - idx1 and idx2 must be valid indices within graph H
                Post-condition:
                - '+' will be returned if the edge exists in both graphs
                - '-' will be returned if the edge doesn't exist in graph G
*/
char getEdgeStatus(graphType *graphG, graphType *graphH, int idx1, int idx2) {
  int gIndex1, gIndex2;

  gIndex1 = findVertexIdx(graphG, graphH->vertices[idx1]);
  gIndex2 = findVertexIdx(graphG, graphH->vertices[idx2]);

  if (gIndex1 == -1 || gIndex2 == -1)
    return '-';

  if (graphG->adjMatrix[gIndex1][gIndex2] != 1)
    return '-';

  return '+';
}

/*
                Purpose: To write on a file if an edge in the second graph
   exists in the first graph or not Returns: void
                @param file The pointer to a file
                @param graphG The pointer to the first graph
                @param graphH The pointer to the second graph
                @param sortedIndices The pointer to an integer array
                Pre-condition:
                - sortedIndices must be sorted prior to calling this function
                - graphG and graphH must be initialized prior to calling this
   function Post-condition:
                - file will be updated with the edges of the second graph
                  and their statuses of being included in the first graph
*/
void writeEdgesStatus(FILE *file, graphType *graphG, graphType *graphH,
                      int *sortedIndices) {
  int i, j, idx1, idx2;
  char status;

  for (i = 0; i < graphH->nVertices; i++) {
    for (j = i + 1; j < graphH->nVertices; j++) {
      idx1 = sortedIndices[i];
      idx2 = sortedIndices[j];

      if (graphH->adjMatrix[idx1][idx2] == 1) {
        status = getEdgeStatus(graphG, graphH, idx1, idx2);
        fprintf(file, "(%s,%s) %c\n", graphH->vertices[idx1],
                graphH->vertices[idx2], status);
      }
    }
  }
}

/*
                Purpose: Searches for a specific vertex in graph G
                Returns: 1 if the vertex is found in graph G, 0 otherwise
                @param pGraphG The pointer to the graph to search in
                @param vertexName The name of the vertex to search for
                Pre-condition:
                - pGraphG must be initialized prior to calling this function
                - vertexName must be a valid string
                Post-condition:
                - 1 will be returned if the vertex is found in graph G
                - 0 will be returned if the vertex is not found in graph G
*/
int findVertex(graphType *pGraphG, char *vertexName) {
  int j;
  int nVertexFound = 0;

  for (j = 0; j < pGraphG->nVertices && nVertexFound == 0; j++) {
    if (strcmp(vertexName, pGraphG->vertices[j]) == 0)
      nVertexFound = 1;
  }

  return nVertexFound;
}

/*
                Purpose: To write on a file if an edge in the second graph
   exists in the first graph or not Returns: void
                @param File The pointer to a file
                @param graphG The pointer to the first graph
                @param graphH The pointer to the second graph
                @param sortedIndices The pointer to an integer array
                Pre-condition:
                - sortedIndices must be sorted prior to calling this function
                - graphG and graphH must be initialized prior to calling this
   function Post-condition:
                - file will be updated with the edges of the second graph
                  and their statuses of being included in the first graph
*/
int allVerticesExist(graphType *pGraphG, graphType *pGraphH) {
  int i;
  int allFound = 1;

  for (i = 0; i < pGraphH->nVertices && allFound; i++) {
    if (!findVertex(pGraphG, pGraphH->vertices[i]))
      allFound = 0;
  }

  return allFound;
}

/*
                Purpose: Checks if a specific edge from graph H exists in graph
   G Returns: 1 if the edge exists in graph G or no edge exists in graph H, 0
   otherwise
                @param pGraphG The pointer to the first graph
                @param pGraphH The pointer to the second graph
                @param nHIndex1 The first vertex index in graph H
                @param nHIndex2 The second vertex index in graph H
                Pre-condition:
                - pGraphG and pGraphH must be initialized prior to calling this
   function
                - nHIndex1 and nHIndex2 must be valid indices within graph H
                Post-condition:
                - 1 will be returned if no edge exists between vertices at
   nHIndex1 and nHIndex2 in graph H or if the edge exists in both graphs
                - 0 will be returned if the edge exists in graph H but not in
   graph G
*/
int checkEdgeExists(graphType *pGraphG, graphType *pGraphH, int nHIndex1,
                    int nHIndex2) {
  int nGIndex1, nGIndex2;

  if (pGraphH->adjMatrix[nHIndex1][nHIndex2] != 1)
    return 1;

  nGIndex1 = findVertexIdx(pGraphG, pGraphH->vertices[nHIndex1]);
  nGIndex2 = findVertexIdx(pGraphG, pGraphH->vertices[nHIndex2]);

  if (nGIndex1 == -1 || nGIndex2 == -1)
    return 0;
  if (pGraphG->adjMatrix[nGIndex1][nGIndex2] == 0)
    return 0;

  return 1;
}

/*
                Purpose: Determines if all edges in graph H exist in graph G
                Returns: 1 if all edges within graph H are also present in graph
   G, 0 otherwise
                @param pGraphG The pointer to the first graph
                @param pGraphH The pointer to the second graph
                Pre-condition:
                - pGraphG and pGraphH must be initialized prior to calling this
   function Post-condition:
                - 1 will be returned if all edges in graph H also exist in graph
   G 0 will be returned if one or more edges in graph H don't exist in graph G
*/
int allEdgesExist(graphType *pGraphG, graphType *pGraphH) {
  int nHIndex1, nHIndex2;
  int allExist = 1;

  for (nHIndex1 = 0; nHIndex1 < pGraphH->nVertices && allExist; nHIndex1++) {
    for (nHIndex2 = 0; nHIndex2 < pGraphH->nVertices && allExist; nHIndex2++) {
      if (pGraphH->adjMatrix[nHIndex1][nHIndex2] == 1) {
        if (!checkEdgeExists(pGraphG, pGraphH, nHIndex1, nHIndex2))
          allExist = 0;
      }
    }
  }

  return allExist;
}

/*
                Purpose: Determines if graph H is a subgraph of graph G
                Returns: void
                @param pGraphG The pointer to the first graph
                @param pGraphH The pointer to the second graph
                @param pIsSubgraph The pointer to an integer that indicates if H
   is a subgraph of G Pre-condition:
                - pGraphG and pGraphH must be initialized prior to calling this
   function Post-condition:
                - pIsSubgraph gains a value of 1 if H is a subgraph of G or a
   value of 0 otherwise
*/
void checkIsSubgraph(graphType *pGraphG, graphType *pGraphH, int *pIsSubgraph) {
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

/*
                Purpose: To write on a file if a graph is a subgraph of another
   graph Returns: void
                @param File The pointer to a file
                @param strBaseG The name of the first graph
                @param strBaseH The name of the second graph
                @param nIsSubgraph The integer that indicates if the first graph
   is a subgraph of the second graph Pre-condition:
                - nIsSubgraph must have a value of either 1 or 0
                Post-condition:
                - pFile will be updated with the conclusion of the first graph
                  being or not being a subgraph of the second graph
*/
void writeSubgraphConclusion(FILE *pFile, String50 strBaseG, String50 strBaseH,
                             int nIsSubgraph) {
  if (nIsSubgraph == 1)
    fprintf(pFile, "%s is a subgraph of %s.\n", strBaseH, strBaseG);

  else
    fprintf(pFile, "%s is not subgraph of %s.\n", strBaseH, strBaseG);
}

/*
                Purpose: To create/write the output file
                Returns: void
                @param strFileG The file name of the first graph with file
   extension
                @param strFileH The file name of the second graph with file
   extension
                @param pGraphG The pointer to the first graph
                @param pGraphH The pointer to the second graph
                Pre-condition:
                - pGraphG and pGraphH must be initialized prior to calling this
   function Post-condition:
                - the output file is created with the corresponding details
   about the vertices, edges, statuses, and conclusion
*/
void produceSubgraphOutput(String50 strFileG, String50 strFileH,
                           graphType *pGraphG, graphType *pGraphH) {
  FILE *pFile;
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

  if (pFile != NULL) {
    sortVerticesAlphabetically(pGraphH, nSortedIndices);
    writeVerticesStatus(pFile, pGraphG, pGraphH, nSortedIndices);
    writeEdgesStatus(pFile, pGraphG, pGraphH, nSortedIndices);

    checkIsSubgraph(pGraphG, pGraphH, &nIsSubgraph);
    writeSubgraphConclusion(pFile, strBaseG, strBaseH, nIsSubgraph);

    fclose(pFile);
  }
}

/*
                Purpose: To read the files of both graphs and get their
   respective details Returns: 1 if both files were successfully read, 0
   otherwise
                @param strFileG The file name of the first graph with file
   extension
                @param strFileH The file name of the second graph with file
   extension
                @param graphG The pointer to the first graph
                @param graphH The pointer to the second graph
                Pre-condition:
                - none
                Post-condition:
                - graphG and graphH are initialized with the contents read from
   their respective files
*/
int readBothGraphFiles(String50 strFileG, String50 strFileH, graphType *graphG,
                       graphType *graphH) {
  int nFileSuccessG, nFileSuccessH;

  nFileSuccessG = readInputFile(strFileG, graphG);

  if (!nFileSuccessG) {
    printf("File %s not found.\n", strFileG);
    return 0;
  }

  nFileSuccessH = readInputFile(strFileH, graphH);

  if (!nFileSuccessH) {
    printf("File %s not found.\n", strFileH);
    return 0;
  }

  return 1;
}

/*
                Purpose: To get the file names of the two graphs to be used
                Returns: void
                @param strFileG The file name of the first graph with file
   extension
                @param strFileH The file name of the second graph with file
   extension Pre-condition:
                - none
                Post-condition:
                - strFileG and strFileH contain the file names of graphs G and H
   respectively
*/
void getInputFilenames(String50 strFileG, String50 strFileH) {
  printf("Input first graph filename: ");
  scanf("%s", strFileG);

  printf("Input second graph filename: ");
  scanf("%s", strFileH);
}

/*
                Purpose: To read the files of two graphs, determine if the
   program continues, find out if one graph is a subgraph of the other, and
   produce an output file. Returns: 0 on exit
*/
int main() {
  graphType graphG, graphH;
  String50 strFileG, strFileH;
  int nCanProceed;

  getInputFilenames(strFileG, strFileH);

  nCanProceed = readBothGraphFiles(strFileG, strFileH, &graphG, &graphH);

  if (nCanProceed == 1) {
    produceSubgraphOutput(strFileG, strFileH, &graphG, &graphH);

    freeAdjList(&graphG);
    freeAdjList(&graphH);
  }

  return 0;
}
