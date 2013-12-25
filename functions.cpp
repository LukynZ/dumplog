
string mpath = "/root/.dumplog/";
string dpath = "/var/log/";

void mkdir() {
  int i = system("mkdir -p /root/.dumplog");                // shell call to create directory
  if (i) {
    cout << "The path can't be created!\n";
    exit(1);
  }
}

string read_shortcuts(string sc) {
  string line;
  ifstream pfile(mpath + "shortcuts");
  if (!pfile.is_open()) {
    return "epic_fail";
  }
  pfile.seekg(0, ios::end);
  if (pfile.tellg() == 0) {
    return "epic_fail";
  }
  pfile.seekg(0, ios::beg);
  while (getline(pfile, line)) {
    int spl = line.find(",");
    if (sc == line.substr(0, spl) && !line.empty()) {
      return line.substr(spl+1, (line.length()-spl));
    }
  }
  return "epic_fail";  
}

void list(string file) {
  string line;
  ifstream pfile(mpath + file);
  while (getline(pfile, line)) {
    cout << line << "\n";
  }
  exit(1);
}

void set_logpath(string path) {
  mkdir();
  ofstream pfile(mpath + "path");                                 // create file with log path
  if (!pfile.is_open()) {
    cout << "Path hasn't been added. Unable to open/create file.\n";
    exit(1);
  }
  if (path.find_last_of("/") == (path.length()-1)) {      // check if path ends with /
    pfile << path;                                          
  } else {
    pfile << path << "/\n";
  }
  pfile.close();
  cout << "Path has been created.\n";
  exit(1);
}

string read_logpath(string path) {
  string line;
  if (path.find("../") != string::npos) {                   // checking for illegal path outside of log directory
    cout << "Illegal source.\n";
    exit(1);
  }
  string conf_path = mpath + "path";
  ifstream pfile(conf_path);
  if (!pfile.is_open()) {
    cout << "Path file does not exists. Using defalt path to log files.\n\n";
    return dpath;
  }
  getline(pfile, line);
  if (!line.empty()) {
    return line;
  } else {
    cout << "Path file is created but empty. Using defalt path to log files.\n\n";
    return dpath;
  }
}

void set_shortcut(string shortc, string file) {
  mkdir();
  ofstream pfile(mpath + "shortcuts", ios::app);
  if (!pfile.is_open()) {
    cout << "Shortcut hasn't been added. Unable to open/create shortcut file.\n";
    exit(1);
  }
  pfile << shortc << "," << file << "\n";
  pfile.close();
  cout << "Shortcut has been set.\n";
  exit(1);
}

string replace(string val,  string line) {
  line.replace(line.find(val), val.length(), colb(7)+val+fres());
  return line;
}