
#include <stdio.h>

// sposób na przekazanie danych do programu
// np. rozmiaru tablicy, ktora bedzie uzyta.

// trzeba zdefiniowac liczba w zasiegu globalnym:

int SIZE = 10;

// potem program glowny:

int main( int argc, char** argv ){

	printf("Domyslna wartosc SIZE = %i\n",SIZE);

	// w programie glownym robimy analize argumentow
	int i=1;
	// zmiennej i nadajemy wartosc 1 i sprawdzamy po kolei argumenty programu z tablicy argv[i]
	// sprawdzenia dokonujemy przez funcje strcmp, ktora zwraca 0, gdy napisy dostanie rowne
	// np. strcmp("hwdp",napis)  ma wartoc zero tylko, w zmiennej napis siedza litery hwdp.
	while( i<argc ){

		// jezeli napis '-size' jest taki sam jak w argv[i], to argv[i+1] musi zawierac liczbe
		// bo zwykle opcje podajemy tak: '-size 50'. Oczywiscie w ciemno zakladamy, ze bedzie
		// liczba na pozycji i+1, ale trudno, jakies ryzyko trzeba poniesc. Zamiast pisac i+1
		// mozna napisac ++i, to to samo, a dodatkowo i bedzie wieksze o jeden juz na stale.
		//
		// Nastepnie napis z pozycji argv[i+1] zamieniamy na liczbe calkowita za pomoca atoi
		// Oczywiscie taki program latwo zabic, wystarczy podac pusty parametr -size i zdechnie.
		if(0 == strcmp("-size",argv[i])){
		        if (argv[++i]) {
			SIZE = atoi(argv[i]);
			}
		}

		i++;
	}

	printf("Nowa wartosc SIZE = %i\n",SIZE);

	return 0;
}



// [c] piotao, 20131007

