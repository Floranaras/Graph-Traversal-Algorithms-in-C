/* main.c */
#include <head.h>
#include <fileInput.h>
#include <graph.h>
#include <transversal.h>

int main()
{
    graphType graph;
    String10 strInputFileName;
    String10 strStartVertex;
    String10 strBaseFileName;
    int nFileExists;
    int nVertexExists;
    int i;
    
    /* Get input filename */
    printf("Input filename: ");
    scanf("%s", strInputFileName);
    
    /* Try to read the file */
    nFileExists = readInputFile(strInputFileName, &graph);
    
    if (nFileExists == 0) {
        printf("File %s not found.\n", strInputFileName);
        return 0;
    }
    
    /* Create base filename for outputs (remove extension) */
    strcpy(strBaseFileName, strInputFileName);
    for (i = 0; i < strlen(strBaseFileName); i++) {
        if (strBaseFileName[i] == '.') {
            strBaseFileName[i] = '\0';
            break;
        }
    }
    
    /* Produce output files 1-4 */
    produceOutputFile1(strBaseFileName, &graph);
    produceOutputFile2(strBaseFileName, &graph);
    produceOutputFile3(strBaseFileName, &graph);
    produceOutputFile4(strBaseFileName, &graph);
    
    /* Get start vertex for traversals */
    printf("Input start vertex for the traversal: ");
    scanf("%s", strStartVertex);
    
    /* Check if vertex exists */
    nVertexExists = findVertexIndex(&graph, strStartVertex);
    
    if (nVertexExists == -1) {
        printf("Vertex %s not found.\n", strStartVertex);
        return 0;
    }
    
    /* Produce traversal output files */
    produceOutputFile5(strBaseFileName, &graph, strStartVertex);
    produceOutputFile6(strBaseFileName, &graph, strStartVertex);
    
    return 0;
}
