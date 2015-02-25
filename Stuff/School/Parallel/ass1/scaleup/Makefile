all: paralleldata parallelfilter

paralleldata: parallel-data-first.c
	gcc-4.9 -fopenmp -std=c99 -o paralleldata.o parallel-data-first.c

parallelfilter: parallel-filter-first.c
	gcc-4.9 -fopenmp -std=c99 -o parallelfilter.o parallel-filter-first.c

clean:
	rm -f $parallel *.o