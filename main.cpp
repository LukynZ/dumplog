#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "./fonts.h"

int main(int argc, char * argv[]) {
  
  if (argc < 2) {
    cout << "Wrong command parameters.\n";
    cout << "The right format is: dumplog <log file name> <optional word filter>\n";
    exit(1);
  }
  
  string test = argv[1];
  if (test.find("../") != string::npos) {
    cout << "Illegal source.\n";
    exit(1);
  }
  
  string source = "/var/log/";
  source += argv[1];
   
  ifstream myfile (source);
      
  if (myfile.is_open()) {
    string line;
    
    cout << colb(1) << "\n<<<---------- " << argv[1] << " ---------->>>" << fres() << "\n";
    
    if (argc == 2) {
      while (getline(myfile,line)) {
        cout << line << "\n";
      }
    }
    else {
      string dump[argc-2];
      for (int i = 2; i < argc; i++) {
	dump[i-2] += colb(2) + "\n " + argv[i] + fres() + "\n\n";
      }
      while (getline(myfile,line)) {
        for (int i = 2; i < argc; i++) {
	  if (line.find(argv[i]) != string::npos) {
	    dump[i-2] += line + "\n";
	  }
	}
      }
      for (int i = 0; i < argc-2; i++) {
        cout << dump[i];
      }
    }
  }

  else {
   cout << "Unable to open log file or log file does not exist.\n";
  }

  myfile.close();
  return 0;
}
