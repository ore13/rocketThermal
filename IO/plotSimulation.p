# plotSimulation.p
set size 1.0, 0.6
set terminal postscript eps enhanced color solid lw 1.5 size 10cm, 10cm
set output "transient_sim.eps"
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set xlabel "Time (s)"
set ylabel "Temperature ({\312}C)"
set grid
set style line 1 lw 15
set style line 2 lw 15
set style line 3 lw 15
plot "output/heatingSimulation100.csv" using 1:2 title 'free stream' with lines, \
"output/heatingSimulation100.csv" using 1:3 title 'boundary layer' with lines, \
"output/heatingSimulation100.csv" using 1:4 title 'skin' with lines