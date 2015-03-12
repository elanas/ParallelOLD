#!/bin/bash

javac CoinFlip.java

declare -i z=32

for i in `seq 1 "$z"`;
    do
        echo -e "\nloop $i"
        java CoinFlip "$i" 1000000000
    done 