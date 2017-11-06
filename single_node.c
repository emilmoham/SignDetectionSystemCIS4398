#include <mpi.h>
#include <stdio.h>

int Master_Node();
int Preprocessor_Node();
int Analyzer_Node();

int main(int argc, char**argv) {

	MPI_Init(NULL, NULL);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(processor_name, &name_len);

	/*printf("Hello world from processor %s, rank %d"
		" out of %d processors\n",
		processor_name, world_rank, world_size);
	*/

	printf(" %d \n", Master_Node());
	printf(" %d \n", Preprocessor_Node());
	printf(" %d \n", Analyzer_Node());
	
	MPI_Finalize();
}


int Master_Node(){

	printf("Hello World from the Master Node");

	return 1;

}

int Preprocessor_Node(){

	printf("Hello World from the Preprocessor Node");
	
	return 2;
}

int Analyzer_Node(){

	printf("Hello World from the Analyzer Node");
	
	return 3;
}
