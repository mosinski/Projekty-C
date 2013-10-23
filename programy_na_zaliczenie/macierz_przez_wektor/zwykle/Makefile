all: mxv

mxv: mxv.c
	gcc mxv.c -lrt -o mxv

run: mxv
	./mxv $(size)

clean: 
	rm -f mxv *.o *~ 
