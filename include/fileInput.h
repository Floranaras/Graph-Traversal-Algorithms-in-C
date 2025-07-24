#ifndef FILEINPUT_H 
#define FILEINPUT_H

#include <head.h>

int readInputFile(String10 strInputFileName, graphType* pGraph);

int findVertexIndex(graphType* pGraph, String10 strVertex);

int createOutputFileName(String10 strInputFileName, char* strSuffix, String50 strOutputFileName);

int compareStrings(String10 str1, String10 str2);

int sortVerticesAlphabetically(graphType* pGraph, int nIndices[]);

#endif
