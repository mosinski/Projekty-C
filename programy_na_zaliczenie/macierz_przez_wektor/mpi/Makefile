all: mxv

mxv: mxv.c
	mpicc mxv.c -lrt -o mxv

run: mxv
	mpirun -np $(np) ./mxv $(size)

clean: 
	rm -f mxv *.o *~ 
