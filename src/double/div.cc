#include <iostream>

using namespace std;


int main() {
    uint64_t num1 = 10001312121121;

    auto num2 = num1 / 1000;
    uint64_t num3 = num1 / 1000;

    std::cout << "num1 = " << num1 << " num2 = " << num2 << " num3 = " << num3 << std::endl;
}