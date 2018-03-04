## Gnuplot script file for plotting data in file "gnu_depth_si.dat"
   
   
   set nomultiplot
   set terminal postscript eps color enhanced solid
   set output "subplot.eps"
   set multiplot
   set xrange[*:*]
   set yrange[*:*]
   set size 0.5,0.5
   set origin 0,0
   
   set title "Money in Bennyland"# font "Helvetica,14"
   set ylabel "GDP / $BJ" #font "Helvetica,10"
   set xlabel "time"# font "Helvetica,10"
   set multiplot
   
   set  pointsize 0.5
   set style line 1 linetype -1 linewidth 2
   set style line 2 linetype 0 linewidth 2
   set style line 3 linetype 1 linewidth 2
   set style line 4 linetype 2 linewidth 2
   set style line 5 linetype 3 linewidth 2
   set style line 6 linetype 4 linewidth 2
   set style line 7 linetype 5 linewidth 2
   set style line 8 linetype 6 linewidth 2

  
   
   plot "money_test.txt" using 1:2 title "Bank Capital" with lines  ls 1, "money_test.txt" using 1:3 title "Bank loans" with linespoints ls 8, "money_test.txt" using 1:4 title "Bank debts" with lines ls 3, "money_test.txt" using 1:5 title "Conusmer capital" with lines  ls 4,  "money_test.txt" using 1:6 title "Company capital" with lines ls 5, "money_test.txt" using 1:7 title "Market capital" with lines ls 6, "money_test.txt" using 1:8 title "Total capital" with lines ls 7
      
      
      set origin 0.5,0
      set xrange [*:*]
      set yrange [*:*]
      
      set title "GDP & stuff in Bennyland"# font "Helvetica,24"
      set ylabel "GDP / $BJ"# font "Helvetica,18"
      set xlabel "time"# font "Helvetica,18"
      plot "gdp_test.txt" using 1:2 title "Real GDP / items" with lines ls 1
	 
	 
	 set origin 0.5,0.5
	 set xrange [*:*]
	 set yrange [*:*]
	 
	 set title "GDP & stuff in Bennyland"# font "Helvetica,24"
      set ylabel "GDP / $BJ"# font "Helvetica,18"
      set xlabel "time"# font "Helvetica,18"
	 
	 plot "gdp_test.txt" using 1:9 title "Investments" with lines ls 5, "gdp_test.txt" using 1:10 title "GDP" with lines ls 8
	    
	    set origin 0,0.5
	    set xrange [*:*]
	    set yrange [0:*]
	    
	    set title "Prices, wages & stuff in Bennyland"# font "Helvetica,24"
	    set ylabel "GDP / $BJ" #font "Helvetica,18"
	    set xlabel "time" #font "Helvetica,18"
	    plot "gdp_test.txt" using 1:8 title "Interest" with lines ls 7, "gdp_test.txt" using 1:7 title "Wages" axes x1y2 with lines ls 6, "gdp_test.txt" using 1:5 title "Price" with lines ls 3,  "gdp_test.txt" using 1:6 title "Employed" axes x1y2 with lines ls 4
	       
