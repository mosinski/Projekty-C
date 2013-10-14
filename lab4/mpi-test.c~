#include <stdio.h> 
#include <mpi.h>

int main(int argc, char **argv) { 

   int rank;
   int size;
   int magic_int = 0;
   int odebrane = 0;
   MPI_Status statusik;

   MPI_Init(&argc,&argv);

   MPI_Comm_size( MPI_COMM_WORLD , &size );
   MPI_Comm_rank( MPI_COMM_WORLD , &rank );

   if ( rank == 0 ){
   magic_int = 666;
   printf("Rank%i: Rozmiar przestrzeni: %d\n", rank , size);
   printf("Rank%i: Wysłałem czekam..\n", rank);
   MPI_Send( &magic_int , 1, MPI_INT, 1, 777, MPI_COMM_WORLD );
   MPI_Recv( &odebrane, 1, MPI_INT, 1, 777, MPI_COMM_WORLD, &statusik);
   printf("Rank%i: Dostałem: %d\n", rank,odebrane);
   }
   
   if ( rank == 1){
         MPI_Recv( &odebrane, 1, MPI_INT, 0, 777, MPI_COMM_WORLD, &statusik);
         printf("Rank%i: Odebrałem: %d\n", rank, odebrane);
         magic_int = odebrane+1;
         printf("Rank%i: Wysłałem: %d\n", rank, magic_int);
         MPI_Send( &magic_int , 1, MPI_INT, 0, 777, MPI_COMM_WORLD );
   }
   printf("Rank%i: Mój numer: %d\n", rank,rank);

   MPI_Finalize();
   return 0;
}
