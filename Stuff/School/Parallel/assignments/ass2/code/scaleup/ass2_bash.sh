#!/bin/bash

rm scaleup.csv
javac CoinFlip.java

declare -i z=16

for i in `seq 1 "$z"`;
    do
        echo -e "\n--- # Threads = $i ---\n" >> scaleup.csv  
        echo -e "\nThread: $i"
        for n in `seq 1 20`;
            do
                declare -i m=$i*1000000
                java CoinFlip "$i" "$m"
            done
    done 
