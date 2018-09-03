#!/usr/bin/gnuplot -persist

set terminal png size 1000,600 linewidth 4 font "Verdana,14"
set termoption dash
set output "collize.png"

#set autoscale
set grid x y
set key left top
unset log
set logscale y
set xlabel "Number of Elements"
set ylabel "Number of collize"
set xrange [10000 : 50000]
#set yrange [1 : 30000]

#set xtics (1, 2, 3, 4, 5, 6, 7, 8, 9)
#set ytics (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
plot "task6.txt" using 1:2 with lines linecolor 1 title "KP", \
        "task6.txt" using 1:3 with lines linecolor 2 title "ADD"
