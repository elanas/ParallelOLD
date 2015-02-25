!/bin/bash

rm paralleloutput.csv
echo -e "**PARALLEL DATA FIRST**\n" >> paralleloutput.csv
make
# gcc-4.9 -fopenmp -std=c99 serial-data-first.c
echo -e "\nParallel Data First\n"

declare -i z=1

for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
	echo -e "\nloop $i\n"
    ./paralleldata.o
    done 

echo -e "\n\n**PARALLEL FILTER FIRST**\n" >> paralleloutput.csv
echo -e "\nParallel Filter First\n"


# gcc-4.9 -fopenmp -std=c99 serial-filter-first.c
for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
    echo -e "\nloop $i\n"
    ./parallelfilter.o
    done 


