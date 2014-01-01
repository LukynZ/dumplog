#ifndef _settings_h
#define _settings_h

class settings {
  
  fstream myfile;
  string line;

public:
    settings (string path);
    ~settings ();
    void set_logpath (string path);
    void set_shortcut (string shortc, string file);
    string check_shortcut (string str, unsigned short& i);
    void list ();
};

settings::settings (string path) {
  string spath {"/root/.dumplog/"};
  int i {system("mkdir -p /root/.dumplog")};
  if (i) {
    cout << "Unable to read/create settings.\nCheck your rights!" << endl;
    exit(1);
  }
  myfile.open(spath+path, ios::out | ios::app);
  myfile.close();
  myfile.open(spath + path);
  if (!myfile.is_open()) {
    cout << "Settings failed. Unable to open/create file." << endl;
    exit(1);
  }
}

settings::~settings () {
  myfile.close();
}

void settings::set_logpath (string path) {
  if (path.find_last_of("/") == (path.length()-1)) {      // check if path ends with /
    myfile << path << endl;                                          
  } else {
    myfile << path << "/" << endl;
  }
  rename("/root/.dumplog/path_", "/root/.dumplog/path");
  cout << "Path has been created." << endl;
}

void settings::set_shortcut (string shortc, string file) {
  if (check_shortcut(shortc, hlpr) == shortc) {
    myfile.clear();
    myfile.seekp(0, ios::end);
    myfile << shortc << "," << file << endl;
    cout << "Shortcut has been set.\n";
  } else {
    char ans[0];
    cout << "This shortcut already exists. Overwrite? (y/n)" << endl;
    cin >> ans;
    if (ans[0] == 'y') {
    ifstream infile("/root/.dumplog/shortcuts");
    ofstream outfile("/root/.dumplog/shortcuts_", ios::out);
    unsigned short x {1};
      while (getline(infile, line)) {
        if (x != hlpr) {
	  outfile << line << endl;
        } else {
	  outfile << shortc << "," << file << endl;
        }
        x++;
      }
      infile.close(); outfile.close();
      rename ("/root/.dumplog/shortcuts_", "/root/.dumplog/shortcuts");
    }
  }
}

string settings::check_shortcut (string str, unsigned short& i) {
  string file {str};
  i = 1;
  while (getline(myfile, line)) {
    unsigned long split {line.find(",")};
    if (str == line.substr(0, split) && !line.empty()) {
      file = line.substr(split+1, (line.length()-split));
      break;
    }
    i++;
  }
  return file;
}

void settings::list () {
  while (getline(myfile, line)) {
    cout << line << "\n";
  }
}

#endif