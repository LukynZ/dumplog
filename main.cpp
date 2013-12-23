#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "./fonts.h"


fstream pfile;
ifstream myfile;
string line;

void create_logpath(string parm) {
  int i = system("mkdir -p /root/.dumplog");                // shell call to create directory
  if (i) {
    cout << "The path can't be created!\n";
    exit(1);
  }
  pfile.open("/root/.dumplog/path", ios::out);              // create file with log path
  if (pfile.is_open()) {
    if (parm.find_last_of("/") == (parm.length()-1)) {      // check if path ends with /
      pfile << parm;                                          
    }
    else {
      pfile << parm << "/";
    }
    pfile.close();
  }
}

void check_logpath(string parm) {
  
  if (parm.find("../") != string::npos) {                   // checking for illegal path outside of log directory
    cout << "Illegal source.\n";
    exit(1);
  }
  
  string path = "/root/.dumplog/path";
  pfile.open(path);
  if (pfile.is_open()) {                                    // checking if log path file exists and if it's open
    getline(pfile, line);
    myfile.open(line+parm);
  }
  else {
    cout << "Path to log directory has not beed specified.\nPlease specify it by: dumplog -p <path>\n(for example: dumplog -p \"/var/log\")\n";
    exit(1);
  }
  
}

string replace(string val,  string line) {
  line.replace(line.find(val), val.length(), colb(7)+val+fres());
  return line;
}

// -------------------------------------------------- M A I N -----------------------------------------------------------------

int main(int argc, char * argv[]) {
  
  if (argc < 2) {                                           // no parameters?
    cout << "Wrong command parameters.\n";
    cout << "The right format is: dumplog <log file name> <optional word filter>\n";
    exit(1);
  }
  
  string arg = argv[1];
  if (arg == "-p") {                                        // if user want to set path
    create_logpath(argv[2]);
    cout <<  "Path created.\n";
    exit(1);
  }  
  else {
    check_logpath(argv[1]);
  }
  
  if (myfile.is_open()) {                                   // check if log file exists and if it's open
    
    cout << colb(1) << "\n<<<---------- " << argv[1] << " ---------->>>" << fres() << "\n";
    
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
