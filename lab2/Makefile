
# ten prosty makefile zrobi kompilacje wszystkich plikow C z katalogu
# uzywajac prostych opcji podanych jako CFLAGS.
# aby dodac biblioteki do programow, trzeba okreslic je w LDFLAGS,
# np. -lm -lrt -pthreads lub -fopenmp

# usuniecie tylko skompilowanych programow po 'make clean'
# zbudowanie wszystkiego na nowo po 'make'.
# Ten makefile buduje wszystkie programy bezwarunkowo.

# Zmienne zawsze pisze sie jako $(...nazwa...), chyba ze sa jednoliterowe
# Zmienna $< to zmienna automatyczna, zawiera nazwe pliku, np. program.c
# Zapis $(nazwa:.x=.y) oznacza ze nazwy ze zmiennej ${nazwa} beda zamienione
# z nazw typu bla.x na nazwy typu bla.y. To taka substytucja prosta :)
# zmienna $@ to nazwa pliku, ktory make chce zrobic, np. moze to byc nazwa bla.o
# (dla $@ rownego bla.o, $< bedzie rowne bla.c, itp.)

# POLECAM DOKUMENTACJE GNU make: http://www.gnu.org/software/make/manual/make.html

GCC      = gcc
CCFLAGS  = -g
LDFLAGS  = 
SOURCES  = ${shell ls *.c}
PROGRAMS = ${SOURCES:.c=.hwdp}
.PHONY: clean
.PHONY: all

all: ${PROGRAMS}

%.o: %.c
	${GCC} ${CCFLAGS} -c $< -o $@

%.hwdp: %.o
	${GCC} ${LDFLAGS} -o ${<:.o=} $<

clean:
	rm -f ${SOURCES:.c=.o} ${SOURCES:.c=}


