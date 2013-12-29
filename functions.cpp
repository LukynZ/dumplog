void readline(int& argc, char * argv[]) {
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

void readline_m(int& argc, char * argv[]) {
  int y;
  for (int i = 2; i < argc; i++) {
    if (!strcmp(argv[i], "-f")) {
      y = i;
      break;
    }
  }
  if (y && y != argc-1) {
    for (int i = 2; i < y; i++) {
      settings shc ("shortcuts");
      logfile log (shc.check_shortcut(argv[i], hlpr));
      log.dumpsel(argc, argv, y+1);
    }
  } else {
    for (int i = 2; i < argc; i++) {
      settings shc ("shortcuts");
      logfile log (shc.check_shortcut(argv[i], hlpr));
      log.dumpall();
    }
  }
}