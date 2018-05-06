#!/bin/bash
# declare STRING variable

STRING="Hello World"
#print variable on a screen
echo $STRING


perl -i -pe 's/Consumer1/2001/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer2/2002/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer3/2003/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer4/2004/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer5/2005/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer6/2006/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer7/2007/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer8/2008/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer9/2009/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer10/2010/g' ./transactions_full_mod.txt
perl -i -pe 's/Consumer/0000/g' ./transactions_full_mod.txt



perl -i -pe 's/Company/0/g' ./transactions_full_mod.txt
perl -i -pe 's/Bank/1/g' ./transactions_full_mod.txt
perl -i -pe 's/Market/2/g' ./transactions_full_mod.txt
perl -i -pe 's/market/2/g' ./transactions_full_mod.txt
perl -i -pe 's/johansson_och_johansson/3/g' ./transactions_full_mod.txt
perl -i -pe 's/benny_enterprises/4/g' ./transactions_full_mod.txt
perl -i -pe 's/limpan_AB/5/g' ./transactions_full_mod.txt
perl -i -pe 's/benny_inc/6/g' ./transactions_full_mod.txt
perl -i -pe 's/bempa_co/7/g' ./transactions_full_mod.txt
perl -i -pe 's/bempa_AB/8/g' ./transactions_full_mod.txt


perl -i -pe 's/Inventory/1/g' ./transactions_full_mod.txt
perl -i -pe 's/Purchase/2/g' ./transactions_full_mod.txt
perl -i -pe 's/Salary/3/g' ./transactions_full_mod.txt
perl -i -pe 's/Dividends/4/g' ./transactions_full_mod.txt
perl -i -pe 's/Dividend/4/g' ./transactions_full_mod.txt
perl -i -pe 's/Interest/5/g' ./transactions_full_mod.txt
perl -i -pe 's/Amortization/6/g' ./transactions_full_mod.txt
perl -i -pe 's/Loan/7/g' ./transactions_full_mod.txt
perl -i -pe 's/Investment/8/g' ./transactions_full_mod.txt
perl -i -pe 's/Deposit/9/g' ./transactions_full_mod.txt