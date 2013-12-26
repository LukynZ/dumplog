class logfile {
  
  ifstream myfile;
  string line;
  string file;

public:
  logfile (string filename) {
    string spath = "/root/.dumplog/path";
    string dpath = "/var/log/";
    string path;
    file = filename;

    myfile.open(spath);
    if (!myfile.is_open()) {
      cout << "\nPath file does not exists. Using defalt path to log files.\n\n";
      path = dpath + file;
    } else {
      getline(myfile, line);
      if (!line.empty()) {
        path = line + file;
      } else {
        path = dpath + file;
        cout << "\nPath file is created but empty. Using defalt path to log files.\n\n";
      }
    }
    myfile.close();
    myfile.open(path);
    if (!myfile.is_open()) {
      cout << "\nUnable to open log file or log file does not exist.\nCheck your path to log files.\n";
      exit(1);
    }
  }
  ~logfile() {
    myfile.close();
    cout << colb(1) << "\nFinished\n" << fres() << endl;
  }
  void dumpall() {
    cout << colb(1) << "\n<<<---------- " << file << " ---------->>>" << fres() << "\n";
    while (getline(myfile,line)) {
      cout << line << "\n";
    }
  }
  void dumpsel(int argc, char * argv[], int y) {
    cout << colb(1) << "\n<<<---------- " << file << " ---------->>>" << fres() << "\n";
    string dump[argc-2];
    for (int i = y; i < argc; i++) {
      dump[i-y] += colb(2) + "\n " + argv[i] + fres() + "\n\n";  // filter paramets
    }
    while (getline(myfile,line)) {
      for (int i = y; i < argc; i++) {                    // filtered lines for every parameter
        if (line.find(argv[i]) != string::npos) {
          dump[i-y] += replace(argv[i], line) + "\n";
        }
      }
    }
    for (int i = 0; i < argc-2; i++) {                    // print out content
      cout << dump[i];
    }
  }
  string replace(string val, string lines) {
    lines.replace(line.find(val), val.length(), colb(7)+val+fres());
    return lines;
  }
};

class settings {
  
  fstream myfile;
  string spath = "/root/.dumplog/";
  string file;
  
public:
  settings(string path) {
    int i = system("mkdir -p /root/.dumplog");
    if (i) {
      cout << "Unable to read/create settings.\nCheck your rights!\n";
      exit(1);
    }
    myfile.open(spath+path, ios::out | ios::app);
    myfile.close();
    myfile.open(spath + path);
    if (!myfile.is_open()) {
      cout << "Settings failed. Unable to open/create file.\n";
      exit(1);
    }
  }
  ~settings() {
    myfile.close();
  }
  void set_logpath(string path) {
    if (path.find_last_of("/") == (path.length()-1)) {      // check if path ends with /
      myfile << path;                                          
    } else {
      myfile << path << "/\n";
    }
    cout << "Path has been created.\n";
  }
  void set_shortcut(string shortc, string file) {
    myfile.seekp(0, ios::end);
    myfile << shortc << "," << file << "\n";
    cout << "Shortcut has been set.\n";
  }
  string check_shortcut(string str) {
    string line;
    while (getline(myfile, line)) {
      int spl = line.find(",");
      if (str == line.substr(0, spl) && !line.empty()) {
	file = line.substr(spl+1, (line.length()-spl));
	break;
      } else {
	file = str;
      }
    }
    return file;
  }
  void list() {
    string line;
    while (getline(myfile, line)) {
      cout << line << "\n";
    }
  }
};

void readline(int& argc, char * argv[]) {
  if (argc == 2 && strcmp(argv[1], "-m")) {
    settings shc ("shortcuts");
    logfile log (shc.check_shortcut(argv[1]));
    log.dumpall();
  } else if (argc > 2 && strcmp(argv[1],"-m")) {
    settings shc ("shortcuts");
    logfile log (shc.check_shortcut(argv[1]));
    log.dumpsel(argc, argv, 2);
  } else {
    int y;
    for (int i = 2; i < argc; i++) {
      if (!strcmp(argv[i], "-f")) {
        y = i;
	break;
      }
    }
    for (int i = 2; i < y; i++) {
      settings shc ("shortcuts");
      logfile log (shc.check_shortcut(argv[i]));
      log.dumpsel(argc, argv, y+1);
    }
  }
}