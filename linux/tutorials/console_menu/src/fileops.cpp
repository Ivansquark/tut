#include "fileops.h"
Fileops::Fileops() { init(); }

void Fileops::init() {
    strList->push_back("FIRST");
    //--------- C -------------------------------------------------------------
    // DIR* dp;
    // int i = 0;
    // struct dirent* ep;
    // dp = opendir("scripts/");
    // if (dp != NULL) {
    //    while (ep = readdir(dp)) i++;
    //    (void)closedir(dp);
    //} else
    //    perror("Couldn't open the directory");
    // std::cout << "files num C = " << i << std::endl;
    //---------- C++ 17 -------------------------------------------------------
    auto dirIter = std::filesystem::directory_iterator("scripts/");
    std::set<std::filesystem::path> sorted_by_name;
    int fileCount = 0;
    for (auto& entry : dirIter) {
        if (entry.is_regular_file()) { sorted_by_name.insert(entry.path()); }
    }
    for (auto& entry : sorted_by_name) {
        std::fstream file(entry, std::ios::in);
        if (file.is_open()) {
            std::string line;
            getline(file, line);
            line = line.substr(1, line.size() - 1);
            strList->push_back(line);
        }
        file.close();
        ++fileCount;
    }

    //std::cout << "files num C++ = " << fileCount << std::endl;

    strList->push_back("LAST");
}
void Fileops::print_files() {
    for (auto& i : *strList) { std::cout << i << std::endl; }
}
