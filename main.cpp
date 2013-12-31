#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int hlpr = 0;

#include "./settings.h"
#include "./logfile.h"
#include "./functions.h"

int main(int argc, char * argv[]) {

  if (argc < 2) {                                           // no parameters?
    dump_cmd();
    exit(1);
  }
  
  if (argv[1][0] != '-') {
    readline (argc, argv);
  } else if (!strcmp(argv[1], "-m") && argc > 2) {
    readline_m (argc, argv);
  } else if (!strcmp(argv[1], "-ls")) {
    settings lst("shortcuts");
    lst.list();
  } else if (!strcmp(argv[1], "-lp")) {
    settings lst("path");
    lst.list();
  } else if (!strcmp(argv[1], "-sp") && argv[2]) {
      settings log ("path_");
      log.set_logpath(argv[2]);
  } else if (!strcmp(argv[1], "-ss") && argv[2] && argv[3]) {
      settings shc ("shortcuts");
      shc.set_shortcut(argv[2], argv[3]);
  } else {
    dump_cmd();
  }
  return 0;
}
