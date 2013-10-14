#include <stdio.h> 
#include <mpi.h>

int main(int argc, char *argv[]) { 

   int rank;
   int size;
   int magic_int = 0;
   int odebrane = 0;
   int nastepny = 0;
   int oczekiwany = 0;
   MPI_Status statusik;

   MPI_Init(&argc,&argv);

   MPI_Comm_size( MPI_COMM_WORLD , &size );
   MPI_Comm_rank( MPI_COMM_WORLD , &rank );

   nastepny = rank+1;
   oczekiwany = rank-1;
   	
   if (rank == 0) {
      oczekiwany = size-1; //ustalam ostatni elemenlt
      printf("Rank%i: Wysłałem do: %d Liczbę: %d\n", rank, nastepny, magic_int);
      MPI_Send( &magic_int , 1, MPI_INT, nastepny, 777, MPI_COMM_WORLD );
   }
   
   printf("Rank%i: Czekam na: %d ..\n", rank, oczekiwany);
   MPI_Recv( &odebrane, 1, MPI_INT, oczekiwany, 777, MPI_COMM_WORLD, &statusik);
   printf("Rank%i: Odebrałem od: %d Liczbę: %d\n", rank, oczekiwany, odebrane);
   magic_int = odebrane+5;//zwikszam liczbę o 5
 
   if (rank == size-1) {
      nastepny = 0;
   }
   
   if (rank != 0 ) {
      printf("Rank%i: Wysłałem do: %d Liczę: %d\n", rank, nastepny,magic_int);
      MPI_Send( &magic_int , 1, MPI_INT, nastepny, 777, MPI_COMM_WORLD );
   }
  
   MPI_Finalize();
}
