#!/bin/bash

rm serialoutput.csv
echo -e "**SERIAL DATA FIRST**\n" >> serialoutput.csv

make
# gcc-4.9 -fopenmp -std=c99 serial-data-first.c

echo -e "\nSerial Data First\n"

declare -i z=20

for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
        echo -e "\nloop $i\n"
	./serialdata.o

    done 

echo -e "\n\n**SERIAL FILTER FIRST**\n" >> serialoutput.csv
echo -e "\nSerial Filter First\n"
# gcc-4.9 -fopenmp -std=c99 serial-filter-first.c
for i in `seq 1 "$z"`;
    do
        # echo -e "\nLOOP:$i" >> output.csv
    echo -e "\nloop $i\n"
    ./serialfilter.o
    done 


