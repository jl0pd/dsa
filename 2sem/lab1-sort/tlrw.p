#!/usr/bin/gnuplot -persist

set terminal png size 1000,600 linewidth 4 font "Verdana,14"
set termoption dash
set output "plot.png"

set autoscale
set grid x y
set key right bottom
unset log
set logscale y
set xlabel "Number of Elements"
set ylabel "Time, seconds"
set xrange [10000 : 1000000]
plot "sort_result.txt" using 1:2 with lines linecolor 1 title "Radix", \
	"sort_result.txt" using 1:3 with lines linecolor 2 title "Odd-Even", \
	"sort_result.txt" using 1:4 with lines linecolor 3 title "Quick"

