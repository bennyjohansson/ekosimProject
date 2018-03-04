## Gnuplot script file for plotting data in file "gnu_depth_si.dat"


   set nomultiplot
   set terminal postscript eps enhanced solid
   set output "h4_blue_depth1000.eps"
   set xrange[0:1200]
   set yrange[0:2400]
   set size 1.5,1
   set key right
   set title "Spatial location of blue peak" font "Helvetica,24"
#set title '{/Symbol=18 \\362@_{/=9.6 0}^{/=16 x}} {/Helvetica e^{-{/Symbol m}^2/2} d}{/Symbol m}'
   set ylabel "Luminescent centres" font "Helvetica,18"
   set xlabel "Depth / nm" font "Helvetica,18"
#set multiplot
#set nolabel
   set  pointsize 3
   set style line 1 linetype -1 linewidth 2
   set style line 2 linetype -1 linewidth 1
   set style line 3 linetype 3 linewidth 2
   set style line 4 linetype 1 linewidth 2
   
   plot "h4_blue_depth1000.dat" using 1:2 title "Blue luminescence" with linespoints  ls 1
set nomultiplot
       
