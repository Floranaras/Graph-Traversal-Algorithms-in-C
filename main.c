#include "graph.c"

int main ()
{
	graphType graph;
	String10 strInputFileName, strStartVertex, strBaseFileName;
	int i, nFileExists, nVertexExists;

	printf("Input filename: ");
	scanf("%s", strInputFileName);

	nFileExists = readFromFile(strInputFileName, &graph);

	if (!nFileExists)
		printf("File %s not found.\n", strInputFileName);
	else
	{
		// entire algo here	
	}

	return 0;
}
