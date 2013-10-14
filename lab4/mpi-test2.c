#include <stdio.h>
#include <mpi.h>

int main( int argc, char **argv ){

	int rank;
	int size;

	int magic_number = 0;
	int odebrane = 0;
	MPI_Status statusik;

	MPI_Init(&argc,&argv);

	MPI_Comm_size( MPI_COMM_WORLD , &size );
	MPI_Comm_rank( MPI_COMM_WORLD , &rank );

	if( rank == 0 ){
		magic_number = 666;
		printf("rank%i: wysylam %i do noda %i\n",rank,magic_number,1);
		MPI_Send( &magic_number, 1,       MPI_INT,               1 ,       777,     MPI_COMM_WORLD );
	}
	if( rank == 1 ){
		printf("rank%i: magic_number = %i\n",rank,magic_number);
		MPI_Recv(&odebrane, 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &statusik);
		printf("rank%i: magic_number = %i (po odbiorze) \n",rank,odebrane);
	}
	
	printf("rank%i: moj numer: %i\n",rank,rank);

	MPI_Finalize();
	return 0;
}

