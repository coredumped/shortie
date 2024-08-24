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
  std::cout << argv[0] << " [PATH]\n";
  std::cout << "Shortens a filesystem path by displaying only a few characters\n per path component.\n\n";
  std::cout << " -h, --help\tDisplay this help message\n";
  std::cout << " -v, --version\tGet version\n";
  std::cout << " --home\t\tReplace home directory with tilde (~)\n";
  std::cout << " --no-home\tInverse of --home\n";
  std::cout << " -n <number>\tCount of characters to print per path component\n";
  std::cout << "\nIf not PATH is given it default to the current working directory.\n";
  exit(EXIT_SUCCESS);
}
