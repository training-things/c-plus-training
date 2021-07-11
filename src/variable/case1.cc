#include <iostream>

int main()
{

    int a = 4;

    std::cout << "a:" << a << std::endl;

    a = 123;
    std::cout << "reset resign a:" << a << std::endl;

    char c = a;
    std::cout << "c:" << c << std::endl;


    // char d = std::move(a);
    // std::cout << "std::move(a) d:" << d << std::endl;
}