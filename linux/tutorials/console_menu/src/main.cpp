#include "fileops.h"

#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <string>
#include <unistd.h>
#include <vector>
std::string arrow = ">>>>> ";

int main() {
    int fd = 0;
    const char* device = "/dev/input/event8";
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
                std::string str = "scripts/";
                std::string num = std::to_string(counter);
                str = str + num;
                system((char*)str.data());
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
