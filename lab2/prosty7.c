
// wlasny typ danych - to bardzo proste

// do podmianki nazw typow sluzy slowo kluczowe typedef
// generalnie to troche oszustwo, ale niewazne.
// Wystarczy napisac:
// typedef stara-nazwa  moja-super-wypasiona-nazwa

// vv - po ponizszej redefinicji, wszystkie liczby calkowite beda traktowane
// tak samo jak 'integer' znany z Pascala.
typedef int integer;


// ladniejszy zapis 3 liczb zmiennoprzecinkowych. Taki typ moze sie przydac
// do zapisu np. wspolrzednych wektora w 3d.

typedef struct {
	double x;
	double y;
	double z;
} double3;

// po deklaracji np.
// double3 A;
// mozemy odwolac sie do elementow za pomoca kropki: A.x, A.y, A.z
// ale jezeli bedzie to wskaznik, wtedy uzywamy strzalki:
// double3 *B;
// odwolanie: B->x, B->y, B->z

// albo mozna w ten sposob zrobic sobie ladna zmienna strukturalna:
// zwykla struktura:

struct OBIAD_MARZENIE {
	int kartofle;
	int schaboszczak;
	int seta;
} obiad_mistrza;

// teraz zmienna obiad_mistrza ma naturalnie typ strukturalny OBIAD_MARZENIE.

// definiowanie ogolnego typu danych:

typedef double Dane;
typedef Dane* pDane;

// teraz typ danych Dane jest tym samym co double (ale zgodnosci kompilator nie widzi)
// a wskaznik na ten typ to 'nowy' typ pDane. Dlatego mozna napisac tak:

#include <stdio.h>
int main(){

	pDane d1;    // - to bedzie wskaznik
	// lub:
	Dane* d2;    // - to jest to samo, ale bardziej brzydko :)

	printf("ten program nic nie robi, poczytaj zrodlo.\n");
}


// [c] piotao, 20131007

