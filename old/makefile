CCC = g++
CCFLAGS = -g -Wall # Kompilera för avlusning main : 
OBJECTS_CC = consumer.cc  consumer_list.cc functions.cc city.cc company.cc company_list.cc
OBJECTS_O = city.o consumer.o consumer_list.o functions.o company.o company_list.o element_company.o element_consumer.o market.o

OBJECTS_O2 = element_consumer.o element_company.o company_list.o consumer_list.o employee_list.o consumer.o company.o functions.o city.o

main : main.o $(OBJECTS_O)
	$(CCC) $(CCFLAGS) main.o $(OBJECTS_O) -o main		

main.o : main.cc
	$(CCC) $(CCFLAGS) -c main.cc

city.o :  city.cc
	$(CCC) $(CCFLAGS) -c city.cc

consumer.o : consumer.cc
	$(CCC) $(CCFLAGS) -c consumer.cc

consumer_list.o : consumer_list.cc
	$(CCC) $(CCFLAGS) -c consumer_list.cc

company.o : company.cc
	$(CCC) $(CCFLAGS) -c company.cc

company_list.o : company_list.cc
	$(CCC) $(CCFLAGS) -c company_list.cc

functions.o : functions.cc
	$(CCC) $(CCFLAGS) -c functions.cc

#employee_list.o :employee_list.cc
#	$(CCC) $(CCFLAGS) -c employee_list.cc

element_company.o : element_company.cc
	$(CCC) $(CCFLAGS) -c element_company.cc

element_consumer.o : element_consumer.cc
	$(CCC) $(CCFLAGS) -c element_consumer.cc

market.o : market.cc
	$(CCC) $(CCFLAGS) -c market.cc
# Städa arbetsmappen 
clean : 
	@ \rm -f *.o