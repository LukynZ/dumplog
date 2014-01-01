#ifndef _logfile_h
#define _logfile_h

#include "./fstyle.h"

class logfile {
  
  ifstream myfile;
  string line;
  string file;

  string highlight (string val);

public:
    logfile (string filename);
    ~logfile ();
    void dumpall();
    void dumpsel (int& argc, char * argv[], unsigned short y);
    
};

logfile::logfile (string filename) {
  string spath {"/root/.dumplog/path"};
  string dpath {"/var/log/"};
  string path;
  file = filename;

  myfile.open(spath);
  if (!myfile.is_open()) {
    cout << "\nPath file does not exists. Using defalt path to log files.\n" << endl;
    path = dpath + file;
  } else {
    getline(myfile, line);
    if (!line.empty()) {
      path = line + file;
    } else {
      path = dpath + file;
      cout << "\nPath file is created but empty. Using defalt path to log files.\n" << endl;;
    }
  }
  myfile.close();
  myfile.open(path);
  if (!myfile.is_open()) {
    cout << "\nUnable to open log file or log file does not exist.\nCheck your path to log files." << endl;;
    exit(1);
  }
}

logfile::~logfile () {
  myfile.close();
  cout << colb(1) << "\nFinished\n" << fres() << endl;
}

void logfile::dumpall () {
  cout << colb(1) << "\n<<<---------- " << file << " ---------->>>" << fres() << endl;;
  while (getline(myfile,line)) {
    cout << line << "\n";
  }
}

void logfile::dumpsel (int& argc, char * argv[], unsigned short y) {
  cout << colb(1) << "\n<<<---------- " << file << " ---------->>>" << fres() << endl;
  string dump[argc-y];
  for (unsigned short i {y}; i < argc; i++) {
    dump[i-y] += colb(2) + "\n " + argv[i] + fres() + "\n\n";  // filter paramets
  }
  while (getline(myfile,line)) {
    for (unsigned short i {y}; i < argc; i++) {                    // filtered lines for every parameter
      if (line.find(argv[i]) != string::npos) {
        dump[i-y] += highlight(argv[i]) + "\n";
      }
    }
  }
  for (unsigned short i {0}; i < argc-y; i++) {                    // print out content
    cout << dump[i];
  }
}

string logfile::highlight (string val) {
  line.replace(line.find(val), val.length(), colb(7)+val+fres());
  return line;
}

#endif