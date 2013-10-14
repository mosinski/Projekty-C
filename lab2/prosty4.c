
// sprawdzenie, czy istnieje plik o nazwie 'plik'

#include <stdio.h>     // obsluga IO, takze funkcja perror


int main( ){

	FILE *file;    // zmienna file to wskaznik typu FILE, do struktury danych opisujacej plik
	
	file = fopen("plik","r");  // otwieranie pliku o nazwie 'plik' w trybie 'read'
	                           // jezeli sie udalo, file NIE jest NULL
	if(file){
		printf("plik '%s' otwarto!\n","plik");
		fclose(file);
	}
	else{
		printf("niestety, pliku '%s' nie dalo sie otworzyc\n","plik");
		perror("przyczyna");
	}
	
	return 0; // ten return mozna pominac - kompilator doda sam.
}

// [c] piotao, 20131007

