## Gnuplot script file for plotting data in file "gnu_depth_si.dat"
   
    x_start = 0
      x_end = 500
   
   set nomultiplot
   set terminal postscript eps color enhanced solid
   set output "money_test.eps"
   #set xrange[x_start:x_end]
   set xrange[*:*]
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

  
   
   plot "money_test.txt" using 1:2 title "Bank Capital" with lines  ls 1, "money_test.txt" using 1:3 title "Bank loans" with lines ls 8, "money_test.txt" using 1:4 title "Bank debts" with lines ls 3, "money_test.txt" using 1:5 title "Conusmer capital" with lines  ls 4,  "money_test.txt" using 1:6 title "Company capital" with lines ls 5, "money_test.txt" using 1:7 title "Market capital" with lines ls 6, "money_test.txt" using 1:8 title "Total capital" with lines ls 7
      
     
      
      set nomultiplot
      set output "gdp_real.eps"
      #set xrange[x_start:x_end]
   		set xrange[*:*]
      set yrange [*:*]
      
      set size 1,1
      set key right
      set title "GDP & stuff in Bennyland" font "Helvetica,24"
      set ylabel "GDP / $BJ" font "Helvetica,18"
      set xlabel "time" font "Helvetica,18"
      plot "gdp_test.txt" using 1:2 title "Real GDP / items" with lines ls 1
	 
	 
	 set nomultiplot
	 set output "gdp_invest.eps"
	 #set xrange[x_start:x_end]
   set xrange[*:*]
	 
	 set size 1,1
	 set key right
	 set title "GDP & stuff in Bennyland" font "Helvetica,24"
      set ylabel "GDP / 	$BJ" font "Helvetica,18"
      set xlabel "time" font "Helvetica,18"
	 plot "gdp_test.txt" using 1:9 title "Investments" with lines ls 5, "gdp_test.txt" using 1:10 title "GDP" with lines ls 8
	    
	    set nomultiplot
	    set output "diverse.eps"
	   #set xrange[x_start:x_end]
   set xrange[*:*]
	    
	    set size 1,1
	    set key right
	    set title "Prices, wages & stuff in Bennyland" font "Helvetica,24"
      set ylabel "GDP / 	$BJ" font "Helvetica,18"
      set xlabel "time" font "Helvetica,18"
	    plot "gdp_test.txt" using 1:5 title "Price" with lines ls 3, "gdp_test.txt" using 1:7 title "Wages" with lines ls 6, "gdp_test.txt" using 1:8 title "1000*Interest rate" with lines ls 7 #,  "gdp_test.txt" using 1:6 title "Employed" with lines ls 4
	       
 
 		set nomultiplot
      set output "employment.eps"
      #set xrange[x_start:x_end]
   set xrange[*:*]
      
      set size 1,1
      set key right
      set title "Employment Bennyland" font "Helvetica,24"
      set ylabel "Employed" font "Helvetica,18"
      set xlabel "time" font "Helvetica,18"
      plot "gdp_test.txt" using 1:6 title "Employed" with lines ls 4
	   
	 