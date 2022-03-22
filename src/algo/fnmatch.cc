#include <iostream>
#include <fnmatch.h>

int main(int argc, char *argv[])
{

    std::string pattern = "*";
    std::string key = "213456543";

    auto r1 = fnmatch(pattern.c_str(), key.c_str(), 0);

    std::cout << "r1: " << r1 << std::endl;
}