#include <string>

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
