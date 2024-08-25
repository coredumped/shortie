#ifndef SHORTIE_H
#define SHORTIE_H
#include <string>

#ifndef DIRECTORY_DIVIDER
#define DIRECTORY_DIVIDER '/'
#endif

#ifndef PROJECT_VERSION
#define PROJECT_VERSION "develop"
#endif


class Shortie {
  private:
  std::string homedir;
  std::string path;
  bool useHomeFolderWildcard = true;
  int charsPerComponent = 2;
  void init();

  public:
  Shortie();

  // Parse command line options
  void parseArgs(int argc, char *argv[]);

  // Shortens the path
  std::string shortened();
};

#endif
