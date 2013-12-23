#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream myfile;
string filename;

#include "./fonts.cpp"
#include "./functions.cpp"

int main(int argc, char * argv[]) {
  
  if (argc < 2) {                                           // no parameters?
    cout << "Wrong command parameters.\n";
    cout << "The right format is: dumplog <log file name> <optional word filter>\n";
    exit(1);
  }
  
  string arg = argv[1];
  
  if (arg == "-p") {                                        // if user want to set path
    if (argv[2]) {
      set_logpath(argv[2]);
    }
    else {
      cout << "Wrong path definition.\n";
      exit(1);
    }
  }  
  
  if (arg == "-s") {                                        // if user want to set shortcut
    if (argv[2] && argv[3]) {
      set_shortcut(argv[2], argv[3]);
    }
    else {
      cout << "Wrong shortcut definition.\n";
      exit(1);
    }
  }

  if (arg == "-lp") {                                       // if user want to show path
    list("path");
  }
  
  if (arg == "-ls") {                                       // if user want to show shortcuts
    list("shortcuts");
  }
  
  string shortcut = read_shortcuts(argv[1]);
  if (shortcut != "epic_fail") {
    string path = read_logpath(shortcut);
    myfile.open(path+shortcut);
    filename = shortcut;
  }
  else {
    string path = read_logpath(argv[1]);
    myfile.open(path+argv[1]);
    filename = argv[1];
  }
  
  
  if (myfile.is_open()) {                                   // check if log file exists and if it's open
    string line;
    
    cout << colb(1) << "\n<<<---------- " << filename << " ---------->>>" << fres() << "\n";
    
    if (argc == 2) {                                        // no filter parametes => dump entire log file
      while (getline(myfile,line)) {
        cout << line << "\n";
      }
    }
    else {
      string dump[argc-2];
      for (int i = 2; i < argc; i++) {
	dump[i-2] += colb(2) + "\n " + argv[i] + fres() + "\n\n";  // filter paramets
      }
      while (getline(myfile,line)) {
        for (int i = 2; i < argc; i++) {                    // filtered lines for every parameter
	  if (line.find(argv[i]) != string::npos) {
	    dump[i-2] += replace(argv[i], line)+"\n";
	  }
	}
      }
      for (int i = 0; i < argc-2; i++) {                    // print out content
        cout << dump[i];
      }
    }
  }

  else {
   cout << "Unable to open log file or log file does not exist.\nCheck your path to log files.\n";
  }

  myfile.close();
  return 0;
}
