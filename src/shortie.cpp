#include <algorithm>
#include <cstdlib>
#include <err.h>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <unistd.h>
#include <config.h>
#include "shortie.h"

void help(int argc, char *argv[]);

Shortie::Shortie() {
  init();
}

void Shortie::init() {
  homedir = getenv("HOME");
}

void Shortie::parseArgs(int argc, char *argv[]) {
  for(int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if(arg == "-h" || arg == "--help") {
      help(argc, argv);
    } else if(arg == "--home") {
      useHomeFolderWildcard = true;
    } else if(arg == "--no-home") {
      useHomeFolderWildcard = false;
    } else if(arg == "-v" || arg == "--version") {
      std::cout << argv[0] << " version " << PROJECT_VERSION << std::endl;
      exit(EXIT_SUCCESS);
    } else if(arg == "-n") {
      if (i + 1 < argc) {
        std::istringstream s(argv[++i]);
        s >> charsPerComponent;
        if(charsPerComponent < 1 || s.fail())
          err(EXIT_FAILURE, "Wrong argument %s for parameter -n", argv[i]);
      }
    } else {
      path = argv[i];
    }
  }
  if(path.size() == 0) {
    char *ospath = getcwd(NULL, 0);
    path = ospath;
  }
}

std::string Shortie::shortened() {
  std::string shortenedPath;
  auto rend = path.rend();
  bool isHomeRelative = false;
  // If path starts with home and useHomeFolderWildcard is true perform replacement
  if(useHomeFolderWildcard && path.find(homedir, 0) == 0) {
    isHomeRelative = true;
    if(path.size() > homedir.size()) {
      rend -= homedir.size();
    } else if(path.size() == homedir.size()) {
      return "~";
    }
  }
  auto rbegin = path.rbegin();
  int effectivePathLength = std::distance(rend, rbegin);
  int effectiveCharsPerComponent = std::clamp(charsPerComponent, 1, effectivePathLength - 2);
  // Ignore last / if present
  if(*rbegin == DIRECTORY_DIVIDER) rbegin++;

  // Capture the last path component
  auto ptr = rbegin;
  while(ptr != rend && *ptr != DIRECTORY_DIVIDER) {
    shortenedPath.append(1, *ptr);
    ptr++;
  }
  // Skip existing / if present
  if(ptr != rend) {
    shortenedPath.append(1, *ptr);
    ptr++;
  }

  while (ptr != rend) {
    if (*ptr == DIRECTORY_DIVIDER) {
      std::string component;
      for(int i = charsPerComponent; i > 0 && (ptr - i) != rend; i--) {
        if(component.size() > 0 && *(ptr - i) == DIRECTORY_DIVIDER) {
          component = "";
          continue;
        }
        component.append(1, *(ptr - i));
      }
      // Debug here
      shortenedPath.append(component);
      shortenedPath.append(1, *ptr);
    }
    ptr++;
  }

  if(isHomeRelative && useHomeFolderWildcard) {
    shortenedPath.append(1, '~');
  }

  std::reverse(shortenedPath.begin(), shortenedPath.end());

  return shortenedPath;
}
