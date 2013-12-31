#ifndef _functions_h
#define _functions_h

void readline (int& argc, char * argv[]) {
  if (argc == 2) {
    settings shc ("shortcuts");
    logfile log (shc.check_shortcut(argv[1], hlpr));
    log.dumpall();
  } else if (argc > 2) {
    settings shc ("shortcuts");
    logfile log (shc.check_shortcut(argv[1], hlpr));
    log.dumpsel(argc, argv, 2);
  } 
}

void readline_m (int& argc, char * argv[]) {
  short y;
  for (short i = 2; i < argc; i++) {
    if (!strcmp(argv[i], "-f")) {
      y = i;
      break;
    }
  }
  if (y && y != argc-1) {
    for (short i = 2; i < y; i++) {
      settings shc ("shortcuts");
      logfile log (shc.check_shortcut(argv[i], hlpr));
      log.dumpsel(argc, argv, y+1);
    }
  } else {
    for (short i = 2; i < argc; i++) {
      settings shc ("shortcuts");
      logfile log (shc.check_shortcut(argv[i], hlpr));
      log.dumpall();
    }
  }
}

void dump_cmd () {
  cout << "Wrong command parameters.\n"
  "The right format is:\n\n"
  "dumplog { log_file | shortcut } [ filter pamameter.. ]\n\n"
  "dumplog -m { log_file | shortcut } [logfile2.. | shortcut2..] [ -f [ filter pamameter.. ] ]\n\n"
  "dumplog { -ls | -lp }\n\n"
  "dumplog -ss shortcut log_file\n\n"
  "dumplog -sp path_to_logs\n" << endl;
}

#endif