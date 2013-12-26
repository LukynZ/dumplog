#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;
string filename;

#include "./fonts.cpp"
#include "./class.cpp"

int main(int argc, char * argv[]) {
  
  if (argc < 2) {                                           // no parameters?
    cout << "Wrong command parameters.\n";
    cout << "The right format is: dumplog <log file name> <optional word filter>\n";
    exit(1);
  }
  
  if (!strcmp(argv[1], "-sp")) {                                        // if user want to set path
    if (argv[2]) {
      settings log ("path");
      log.set_logpath(argv[2]);
    } else {
      cout << "Wrong path definition.\n";
      exit(1);
    }
  } else if (!strcmp(argv[1], "-ss")) {                                        // if user want to set shortcut
    if (argv[2] && argv[3]) {
      settings shc ("shortcuts");
      shc.set_shortcut(argv[2], argv[3]);
    } else {
      cout << "Wrong shortcut definition.\n";
      exit(1);
    }
  } else if (!strcmp(argv[1], "-lp")) {                                       // if user want to show path
    settings lst("path");
    lst.list();
  } else if (!strcmp(argv[1], "-ls")) {                                       // if user want to show shortcuts
    settings lst("shortcuts");
    lst.list();
  } else {
    readline (argc, argv);
  }
  
  return 0;
}
