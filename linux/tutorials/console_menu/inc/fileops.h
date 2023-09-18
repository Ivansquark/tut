#ifndef FILEOPS_H
#define FILEOPS_H

#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <list>
#include <memory>
#include <set>

class Fileops {
  public:
    Fileops();
    void print_files();
    std::unique_ptr<std::list<std::string>> strList =
        std::make_unique<std::list<std::string>>(std::list<std::string>());

  private:
    void init();
};

#endif // FILEOPS_H
