#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>

using namespace std;
string filename;
int hlpr = 0;

#include "./fstyle.cpp"
#include "./class.cpp"
#include "./functions.cpp"

int main(int argc, char * argv[]) {

  if (argc < 2) {                                           // no parameters?
    cout << "Wrong command parameters.\n";
    cout << "The right format is: dumplog <log file name> <optional word filter>\n";
    exit(1);
  }
  
  if (!strcmp(argv[1], "-m") && argc > 2) {
    readline_m (argc, argv);
  } else if (!strcmp(argv[1], "-ls")) {
    settings lst("shortcuts");
    lst.list();
  } else if (!strcmp(argv[1], "-lp")) {
    settings lst("path");
    lst.list();
  } else if (!strcmp(argv[1], "-sp")) {
    if (argv[2]) {
      settings log ("path_");
      log.set_logpath(argv[2]);
    } else {
      cout << "Wrong path definition.\n";
      exit(1);
    }
  } else if (!strcmp(argv[1], "-ss")) {
    if (argv[2] && argv[3]) {
      settings shc ("shortcuts");
      shc.set_shortcut(argv[2], argv[3]);
    } else {
      cout << "Wrong shortcut definition.\n";
      exit(1);
    }
  } else if (argv[1][0] == '-') {
    cout << "Wrong command parameters.\n";
    exit(1);
  } else {
    readline (argc, argv);
  }
  
  return 0;
}
