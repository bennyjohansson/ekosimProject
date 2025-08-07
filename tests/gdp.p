## Gnuplot script file for plotting data in file "gnu_depth_si.dat"


   set nomultiplot
   set terminal postscript eps color enhanced solid
   set output "gdp.eps"
   set xrange[0:*]
   set yrange[0:*]
   set size 1,1
   set key left
   set title "GDP for Bennyland" font "Helvetica,24"
#set title '{/Symbol=18 \\362@_{/=9.6 0}^{/=16 x}} {/Helvetica e^{-{/Symbol m}^2/2} d}{/Symbol m}'
   set ylabel "GDP / $BJ" font "Helvetica,18"
   set xlabel "time / months" font "Helvetica,18"
#set multiplot
#set nolabel
   set  pointsize 0.5
   set style line 1 linetype -1 linewidth 2
   set style line 2 linetype 2 linewidth 2
   set style line 3 linetype 3 linewidth 2
   set style line 4 linetype 1 linewidth 2
   set style line 5 linetype 6 linewidth 2
   set style line 6 linetype 5 linewidth 2
   set style line 7 linetype 4 linewidth 2
   
   plot "gdp.txt" using 1:2 title "real GDP" with linespoints  ls 1, "gdp.txt" using 1:5 title "Wages" with linespoints ls 3, "gdp.txt" using 1:6 title "Price" with linespoints ls 4, "gdp.txt" using 1:4 title "Marginal consumption" with linespoints  ls 5,  "gdp.txt" using 1:7 title "No of people employeed" with linespoints ls 2, "gdp.txt" using 1:10 title "Interest rate" with linespoints ls 6, "gdp.txt" using 1:11 title "Invested capital" with linespoints ls 7


      set nomultiplot
      set output "money.eps"
      set xrange [*:*]	     
      set yrange [*:*]
      set key right
      plot "gdp.txt" using 1:8 title "Consumer capital" with lines ls 4, "gdp.txt" using 1:9 title "Company capital" with lines ls 2, "gdp.txt" using 1:12 title "Market capital" with linespoints ls 3, "gdp.txt" using 1:13 title "Bank capital" with linespoints ls 5, "gdp.txt" using 1:14 title "Total capital" with linespoints ls 1
       
	 set nomultiplot
      set output "flash.eps"
      set xrange [*:*]	     
      set yrange [-400000:700000]
      set key right
      plot "flash.txt" using 1:2 title "Consumer capital" with lines ls 4, "flash.txt" using 1:3 title "Company capital" with lines ls 2, "flash.txt" using 1:4 title "Market capital" with linespoints ls 3, "flash.txt" using 1:5 title "Bank capital" with linespoints ls 5, "flash.txt" using 1:6 title "Total capital" with linespoints ls 1
