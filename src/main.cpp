#include <cstdlib>
#include <err.h>
#include <iostream>
#include <unistd.h>
#include "shortie.h"

void help(int argc, char *argv[]);


int main(int argc, char *argv[]) {
  Shortie s;
  s.parseArgs(argc, argv);
  std::cout << s.shortened();
  std::cout.flush();
  return EXIT_SUCCESS;
}


void help(int argc, char *argv[]) {
  std::cerr << argv[0] << " [PATH]\n";
  exit(EXIT_SUCCESS);
}
