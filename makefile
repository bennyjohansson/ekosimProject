CCC = c++ #clang++ #g++ #g++
#CCFLAGS = -g -Wall -std=c++17 # Kompilera f�r avlusning main : 
#OBJECTS_O = city.o consumer.o consumer_list.o functions.o company.o company_list.o element_company.o element_consumer.o market.o clock.o bank.o init_company.o

CCFLAGS = -g -Wall -v   -lsqlite3 -std=c++17 -lstdc++  -W #-L/usr/lib64/mysql/ -lmysqlclient  #-I/usr/local/include -I/usr/local/opt/sqlite/include -L/usr/local/opt/sqlite/lib -stdlib=libc++ -I/usr/lib64/mysql/
OBJECTS_O = world.o city.o consumer.o city_list.o consumer_list.o functions.o company.o company_list.o element_city.o element_company.o element_consumer.o market.o clock.o bank.o SQLfunctions.o #init_company.o 
#OBJECTS_CC = city.o consumer.o consumer_list.o functions.o company.o company_list.o element_company.o element_consumer.o market.o clock.o bank.o init_company.o SQLfunctions.o

main : main.cc $(OBJECTS_O)
	$(CCC) $(CCFLAGS) main.cc $(OBJECTS_O) -o main		

main.o : main.cc
	$(CCC) $(CCFLAGS) -c main.cc

world.o :  world.cc
	$(CCC) $(CCFLAGS) -c world.cc

city.o :  city.cc
	$(CCC) $(CCFLAGS) -c city.cc

consumer.o : consumer.cc
	$(CCC) $(CCFLAGS) -c consumer.cc

city_list.o : city_list.cc
	$(CCC) $(CCFLAGS) -c city_list.cc

consumer_list.o : consumer_list.cc
	$(CCC) $(CCFLAGS) -c consumer_list.cc

company.o : company.cc
	$(CCC) $(CCFLAGS) -c company.cc

company_list.o : company_list.cc
	$(CCC) $(CCFLAGS) -c company_list.cc

functions.o : functions.cc
	$(CCC) $(CCFLAGS) -c functions.cc

element_city.o : element_city.cc
	$(CCC) $(CCFLAGS) -c element_city.cc

element_company.o : element_company.cc
	$(CCC) $(CCFLAGS) -c element_company.cc

element_consumer.o : element_consumer.cc
	$(CCC) $(CCFLAGS) -c element_consumer.cc

market.o : market.cc
	$(CCC) $(CCFLAGS) -c market.cc

clock.o : clock.cc
	$(CCC) $(CCFLAGS) -c clock.cc

bank.o : bank.cc
	$(CCC) $(CCFLAGS) -c bank.cc

# init_company.o : init_company.cc
# 	$(CCC) $(CCFLAGS) -c init_company.cc
	
SQLfunctions.o : SQLfunctions.cc
	$(CCC) $(CCFLAGS) -c SQLfunctions.cc

# St�da arbetsmappen 
clean : 
	@ \rm -f *.o
	@ \rm -f *~

mop :
	@ \rm -f *~
