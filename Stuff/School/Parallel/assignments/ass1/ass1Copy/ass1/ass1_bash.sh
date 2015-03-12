#!/bin/bash

rm serialoutput.csv
echo -e "**SERIAL DATA FIRST**\n" >> serialoutput.csv
make
# gcc-4.9 -fopenmp -std=c99 serial-data-first.c
declare -i z=3

for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
	./serialdata
    done 

echo -e "\n\n**SERIAL FILTER FIRST**\n" >> serialoutput.csv

# gcc-4.9 -fopenmp -std=c99 serial-filter-first.c
for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
    ./serialfilter
    done 


