#include <iostream>

int main(){

    char buf[32];
    auto a1 = std::snprintf(buf, 32, "%016llx", 123121);

    std::cout << "buf:: " << buf << std::endl;

}