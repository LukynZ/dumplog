#ifndef _fstyle_h
#define _fstyle_h

// bold and colored output
string colb(int val) { 
  string color;
  switch (val) {
    case 1:
      color = "\033[1;31m"; break; // red
    case 2:
      color = "\033[1;32m"; break; // green 
    case 3:
      color = "\033[1;33m"; break; // yellow
    case 4:
      color = "\033[1;34m"; break; // blue
    case 6:
      color = "\033[1;36m"; break; // cyan
    case 7:
      color = "\033[1;37m"; // white
  }
  return color;
}

// reset font color and style
string fres() {
  return  "\033[0m";
}

#endif