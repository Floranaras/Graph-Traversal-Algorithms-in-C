#include "graph.c"

int main ()
{
    graphType graph;
    String50 strInputFileName, strStartVertex, strBaseFileName;
    int nFileExists;

    printf("Input filename: ");
    scanf("%s", strInputFileName);

    nFileExists = readInputFile(strInputFileName, &graph);

    if (nFileExists == 0)
        printf("File %s not found.\n", strInputFileName);
    else
    {
        printf("Input starting label: ");
        scanf("%s", strStartVertex);

        // entire algo here	
        getBaseFileName(strBaseFileName, strInputFileName);

        produceOutputFile1 (strBaseFileName, &graph);
        produceOutputFile2 (strBaseFileName, &graph);
        produceOutputFile3 (strBaseFileName, &graph);
        produceOutputFile4 (strBaseFileName, &graph);
        produceOutputFile5 (strBaseFileName, &graph, strStartVertex);

        freeAdjList(&graph);
    }

    return 0;
}
