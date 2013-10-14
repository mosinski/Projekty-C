#include <stdio.h> 
#include <mpi.h>

int main(int argc, char *argv[]) { 

   int rank;
   int size;
   int BARDZO_WAZNA_ZMIENNA = 0;

   MPI_Status statusik;

   MPI_Init(&argc,&argv);

   MPI_Comm_size( MPI_COMM_WORLD , &size );
   MPI_Comm_rank( MPI_COMM_WORLD , &rank );

   if( rank == 0 ) {
     BARDZO_WAZNA_ZMIENNA = 12;
   }

   MPI_Bcast(&BARDZO_WAZNA_ZMIENNA, 1, MPI_INT, 0, MPI_COMM_WORLD);
   printf("rank%i: dostałem zmienną: %d\n", rank, BARDZO_WAZNA_ZMIENNA);
  
   MPI_Finalize();
}
