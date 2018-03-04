## Gnuplot script file for plotting data in file "gnu_depth_si.dat"

#flash << flash_counter_ << " " << consumer_capital << " " << company_capital << " "  << market_capital << " " << bank_capital << " " << total_capital << endl;

   set nomultiplot
   set terminal postscript eps color enhanced solid
   set output "flash.eps"
   set xrange[0:*]
   set yrange[*:*]
   set size 1,1
   set key right
   set title "Money in Bennyland" font "Helvetica,24"
#set title '{/Symbol=18 \\362@_{/=9.6 0}^{/=16 x}} {/Helvetica e^{-{/Symbol m}^2/2} d}{/Symbol m}'
   set ylabel "GDP / $BJ" font "Helvetica,18"
   set xlabel "time" font "Helvetica,18"
#set multiplot
#set nolabel
   set  pointsize 0.5
   set style line 1 linetype -1 linewidth 2
   set style line 2 linetype 0 linewidth 2
   set style line 3 linetype 1 linewidth 2
   set style line 4 linetype 2 linewidth 2
   set style line 5 linetype 3 linewidth 2
   set style line 6 linetype 4 linewidth 2
   set style line 7 linetype 5 linewidth 2
   set style line 8 linetype 6 linewidth 2

   
   plot "flash.txt" using 1:2 title "Consumer Capital" with linespoints  ls 1, "flash.txt" using 1:3 title "Company Capital" with linespoints  ls 2, "flash.txt" using 1:4 title "Market Capital" with linespoints  ls 3, "flash.txt" using 1:5 title "Bank Capital" with linespoints  ls 4, "flash.txt" using 1:6 title "Total Capital" with linespoints  ls 5 




