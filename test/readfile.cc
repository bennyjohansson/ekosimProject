#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


int main() {

  double tal1 = 234234;
  double tal2 = 0.00345345345;
  double tal3 = 1/7;
  string line;

  ifstream myfile ("example.txt");
  if (myfile.is_open()) {
    while (! myfile.eof() )
      {
	getline (myfile,line);
	cout << line << endl;
      }
  }
  else {
    cout << "Unable to open file" << endl; 
  }

  ofstream ou("example.txt", ios::app);
  if(ou.is_open()) { 
    // ou << "Sköna sköna bröst" << endl << "Pussa pussa pussa" << tal3 << endl  << "Balle" << endl 
    cout << tal2 << endl;
    ou.close();
  }
  else {
    cout << "Unable to open file" << endl; 
  }

  //myfile.open();
  if (myfile.is_open()) {
    while (! myfile.eof() )
      {
	getline (myfile,line);
	cout << line << endl;
      }
    myfile.close();
  }
  else {
    cout << "Unable to open file" << endl; 
  }

  
  //  ShellExecute("gnuplot gdp.p");
  //cout << "hej" << endl; 
  //ShellExecute("ls -l");

  char kalle[100];
  char olle[100];
  string olle2 = "1.2423";
  double talet = 0;

  

  strcpy(kalle, olle2.c_str()); 

  talet = atol(kalle);
 
  cout << kalle << endl;

  talet = tal2 + talet;

  cout << talet << endl;

  return 0;

}
