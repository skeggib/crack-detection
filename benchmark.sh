#!/bin/bash

if [ $# -lt 3 ]; then
    echo "usage: $0 <algorithm> <precision> <recall> <images_folder>"
    exit
fi

algorithm=$1
precision=$2
recall=$3
folder=$4

inputs=("6192.jpg" "6193.jpg" "6194.jpg" "6195.jpg" "v001.ppm" "v002.ppm" "v003.ppm" "v004.ppm")
reals=("6192.bmp" "6193.bmp" "6194.bmp" "6195.bmp" "t001.pgm" "t002.pgm" "t003.pgm" "t004.pgm")

rm scores.csv

for (( i=0; i<${#inputs[@]}; i++ )); do
    input=${inputs[$i]}
    real=${reals[$i]}
    ./$algorithm $folder/$input output.png
    p=`./$precision $folder/$real output.png`
    r=`./$recall $folder/$real output.png`
    echo "$input: $p $r"
    echo "$p, $r" >> scores.csv
done
