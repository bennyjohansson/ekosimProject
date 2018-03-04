 
function n = reload(length3)
    
     matr = load gdp_test.txt;

     length = 1;

     length1 = size(matr(:,1))(1)
     length2 = size(matr(:,2))(1)
   
   
         axis
         grid on
    
     #figure(1)
     subplot(1,2,1)
   gplot  matr using 1:5 title "Price" with linespoints, matr using 1:7 title "Wages" with linespoints, matr using 1:8 title "1000*Interest rate",  matr using 1:6 title "Employed"
             subplot(1,2,2)
   gplot  matr using 1:9 title "Investments" with linespoints, matr using 1:10 title "Nominal GDP" with linespoints
    

         lenght = length1;
       replot;
     

     n = length

endfunction
