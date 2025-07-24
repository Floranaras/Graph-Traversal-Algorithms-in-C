#ifndef TRANSVERSAL_H
#define TRANSVERSAL_H

#include <head.h>
#include <fileInput.h>

int performBfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[]);

int performDfsRecursive(graphType* pGraph, int nCurrentVertex, int nVisited[], String10 strResult[], int* pResultCount);

int performDfsTraversal(graphType* pGraph, int nStartIndex, String10 strResult[]);

int produceOutputFile5(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex);

int produceOutputFile6(String10 strOutputFileName, graphType* pGraph, String10 strStartVertex);

#endif
