#include <iostream>
#include <memory>
#include "data_a.h"


DataA::DataA(/* args */) : Base("db_name") {
    std::cout << "DataA::DataA" << std::endl;
}


int main() {
    auto _ptr = std::unique_ptr<DataA>(new DataA());

    std::cout << _ptr << std::endl;
}