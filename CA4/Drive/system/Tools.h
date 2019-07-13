#include <vector>
#include <string>

#ifndef DRIVE_TOOLS_H
#define DRIVE_TOOLS_H


class Tools {
public:
    static std::vector<std::string> split(std::string line, char c);

private:
    Tools();
};


#endif
