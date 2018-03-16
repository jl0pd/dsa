#!/usr/bin/gnuplot -persist

set terminal png size 1000,600 linewidth 4 font "Verdana,14"
set termoption dash
set output "plot.png"

set autoscale
set grid x y
set key right bottom
unset log
set xlabel "Running threads"
set ylabel "Speedup"
set xrange [1 : 9]
set yrange [0 : 9]
set xtics (1, 2, 3, 4, 5, 6, 7, 8, 9)
set ytics (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
plot "tlrw.dat" using 1:2 title "Linear" with linespoints pt 1 lt rgb "violet" dashtype 1, \
    "tlrw.dat" using 1:3 title "N = 3000" with linespoints pt 2 lt rgb "cyan", \
    "tlrw.dat" using 1:4 title "N = 5000" with linespoints pt 12 lt rgb "blue"
