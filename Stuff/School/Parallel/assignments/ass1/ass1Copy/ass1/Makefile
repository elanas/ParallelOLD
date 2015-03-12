all: serialdata serialfilter

serialdata: serial-data-first.c
	gcc-4.9 -fopenmp -std=c99 -o serialdata.o serial-data-first.c

serialfilter: serial-filter-first.c
	gcc-4.9 -fopenmp -std=c99 -o serialfilter.o serial-filter-first.c

clean:
	rm -f $serial *.o