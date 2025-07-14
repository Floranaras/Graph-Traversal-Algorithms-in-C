#include "graph.c"

int main ()
{
	graphType graph;
	String10 strInputFileName, strStartVertex, strBaseFileName;
	int nFileExists, nVertexExists;

	printf("Input filename: ");
	scanf("%s", strInputFileName);

	nFileExists = readInputFile(strInputFileName, &graph);

	if (nFileExists == 0)
		printf("File %s not found.\n", strInputFileName);
	else
	{
		// entire algo here	
        getBaseFileName(strBaseFileName, strInputFileName);

        produceOutputFile1 (strBaseFileName, &graph);
	}

	return 0;
}
