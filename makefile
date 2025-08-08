# Modern C++ compiler settings
CCC = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g -O2
LDFLAGS = -lsqlite3

# Debug build flags (uncomment for debugging)
# CXXFLAGS = -std=c++20 -Wall -Wextra -g -O0 -DDEBUG
OBJECTS_O = world.o city.o consumer.o city_list.o consumer_list.o functions.o company.o company_list.o element_city.o element_company.o element_consumer.o market.o clock.o bank.o SQLfunctions.o #init_company.o 
#OBJECTS_CC = city.o consumer.o consumer_list.o functions.o company.o company_list.o element_company.o element_consumer.o market.o clock.o bank.o init_company.o SQLfunctions.o

main : main.cc $(OBJECTS_O)
	$(CCC) $(CXXFLAGS) main.cc $(OBJECTS_O) $(LDFLAGS) -o main		

main.o : main.cc
	$(CCC) $(CXXFLAGS) -c main.cc

world.o :  world.cc
	$(CCC) $(CXXFLAGS) -c world.cc

city.o :  city.cc
	$(CCC) $(CXXFLAGS) -c city.cc

consumer.o : consumer.cc
	$(CCC) $(CXXFLAGS) -c consumer.cc

city_list.o : city_list.cc
	$(CCC) $(CXXFLAGS) -c city_list.cc

consumer_list.o : consumer_list.cc
	$(CCC) $(CXXFLAGS) -c consumer_list.cc

company.o : company.cc
	$(CCC) $(CXXFLAGS) -c company.cc

company_list.o : company_list.cc
	$(CCC) $(CXXFLAGS) -c company_list.cc

functions.o : functions.cc
	$(CCC) $(CXXFLAGS) -c functions.cc

element_city.o : element_city.cc
	$(CCC) $(CXXFLAGS) -c element_city.cc

element_company.o : element_company.cc
	$(CCC) $(CXXFLAGS) -c element_company.cc

element_consumer.o : element_consumer.cc
	$(CCC) $(CXXFLAGS) -c element_consumer.cc

market.o : market.cc
	$(CCC) $(CXXFLAGS) -c market.cc

clock.o : clock.cc
	$(CCC) $(CXXFLAGS) -c clock.cc

bank.o : bank.cc
	$(CCC) $(CXXFLAGS) -c bank.cc
	
SQLfunctions.o : SQLfunctions.cc
	$(CCC) $(CXXFLAGS) -c SQLfunctions.cc

# St�da arbetsmappen 
clean : 
	@ \rm -f *.o
	@ \rm -f *~

mop :
	@ \rm -f *~
