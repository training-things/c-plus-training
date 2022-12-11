#include <stdio.h>
#include <assert.h>
#include <iostream>


int main()
{
    bool d = true;
    assert(d); 
    // assert
    // d=false will coredump
    // d=true not coredump

    std::cout << "hello" << std::endl;

    return 0;
}