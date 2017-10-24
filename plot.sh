#!/bin/sh
gnuplot << EOF
set terminal png 
set output "$1.png"
set xlabel "Time"
set ylabel "Voltage"
set title "Voltage in time"

plot "$1" using 2:1 with linespoints lw 1 lt rgb 'purple'
EOF
