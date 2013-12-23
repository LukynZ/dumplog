// bold and colored output
string colb(int val) { 
  string color;
  switch (val) {
    case 1:
      color = "\033[1;31m";                                 //  red
      break;
    case 2:
      color = "\033[1;32m";                                 // green
      break;
    case 3:
      color = "\033[1;33m";                                 // yellow
      break;
    case 4:
      color = "\033[1;34m";                                 // blue
      break;
    case 6:
      color = "\033[1;36m";                                 // cyan
      break;
    case 7:
      color = "\033[1;37m";                                 // white
  }
  
  return color;
}

// reset font color and style
string fres() {
  return  "\033[0m";
}
