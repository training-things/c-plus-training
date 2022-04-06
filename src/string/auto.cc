#include <iostream>
#include <string>

// https://blog.csdn.net/u011241498/article/details/102482272

std::string foo()
{
    return "hello";
}

int main()
{
    auto o1 = foo();
    const auto &o2 = foo();
    auto &&o3 = foo();
    std::cout << o1.c_str() << std::endl;
    std::cout << o2.c_str() << std::endl;
    std::cout << o3.c_str() << std::endl;
}