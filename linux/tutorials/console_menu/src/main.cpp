#include "fileops.h"

#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <map>
#include <string>
#include <unistd.h>
#include <vector>
std::string arrow = ">>>>> ";

int main() {
    int fd = 0;
    // const char* device = "/dev/input/event8";
    const char* device =
        "/dev/input/by-id/usb-SQUARK_USB_GAMING_0123456789-if02-event-kbd";
    struct input_event event;
    // event.type = EV_KEY; event.value = EV_PRESSED; event.code = KEY_UP;
    int key = 0;
    uint8_t counter = 1;
    std::vector<std::string> l;

    Fileops fops;
    fops.print_files();
    const size_t fileNums = fops.strList->size();
    std::cout << fileNums << std::endl;
    std::vector<std::string> tempList;
    tempList.reserve(fileNums + 1);
    while (key != KEY_ESC) {
        for (auto i : *fops.strList) { tempList.push_back(i); }
        if (counter >= fileNums - 1) {
            counter = fileNums - 2;
        } else if (counter < 1) {
            counter = 1;
        }
        tempList[counter - 1] = "\t" + tempList[counter - 1];
        tempList[counter + 1] = "\t" + tempList[counter + 1];
        tempList[counter] = arrow + tempList[counter];
        for (int i = counter - 1; i < counter + 2; i++) {
            l.push_back(std::move(tempList[i]));
        }
        tempList.clear();
        usleep(100000);
        system("clear");
        // ------------   Key handler   ---------------------------------------
        for (auto i : l) { std::cout << i << std::endl; }
        l.clear();

        if ((fd = open(device, O_RDWR)) > 0) {
            read(fd, &event, sizeof(input_event));
            key = event.code;
            if (key == KEY_UP) {
                if (counter) { counter--; }
            } else if (key == KEY_DOWN) {
                counter++;
            } else if (key == KEY_ENTER) {
                // std::string str = "scripts/";
                std::map<const int, std::string> fileNames;
                int tempCounter = 1;

                auto dirIter = std::filesystem::directory_iterator("scripts/");
                std::set<std::filesystem::path> sorted_by_name;
                for (auto& entry : dirIter) {
                    if (entry.is_regular_file()) {
                        sorted_by_name.insert(entry.path());
                    }
                }
                for (auto& entry : sorted_by_name) {
                    std::string str = entry;
                    auto z = std::pair<int, std::string>(tempCounter, str);
                    fileNames.insert(z);
                    tempCounter++;
                    //std::cout << str << "\t";
                }
#if 0
                for (auto& p :
                    std::filesystem::directory_iterator("scripts/")) {
                    std::string str = p.path();
                    auto z = std::pair<int, std::string>(tempCounter, str);
                    fileNames.insert(z);
                    // fileNames.insert(std::pair<const int,
                    // std::string>(tempCounter, p));
                    tempCounter++;
                    // std::cout << str << "\t";
                }
#endif
                std::string fullPath = fileNames[counter];
                //std::cout << "\n" << fullPath << std::endl;
                system((char*)fullPath.data());
                // std::string num = std::to_string(counter);
                // str = str + num;
                // system((char*)str.data());
                goto EXIT;
            }
            close(fd);
        }
    }
    return 0;
EXIT:
    close(fd);
    exit(0);
}
