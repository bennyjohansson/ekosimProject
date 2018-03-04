function n = plotting()

     matr = load gdp_test.txt;
 
     
figure(1)
     length = size(matr(:,1))(1);

   for i = 1:1000000000
        pause(1)
        length3 = reload(length)
     length = length3;
   end




end
