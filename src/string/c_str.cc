#include <iostream>
#include <string>
std::string foo()
{
    return std::string("foo");
}
std::string bar0()
{
    return std::string(foo().c_str());
}
std::string bar1()
{
    const char *tmp = foo().c_str();
    return std::string(tmp);
}
std::string bar2()
{
    std::string foo_copy = foo();
    const char *tmp = foo_copy.c_str();
    return std::string(tmp);
}

std::string bar3()
{
    std::string foo_copy = foo();
    return std::string(foo_copy.c_str());
}

int main()
{
    std::cout << "bar0(): " << bar0() << std::endl;
    std::cout << "bar1(): " << bar1() << std::endl;
    std::cout << "bar2(): " << bar2() << std::endl;
    std::cout << "bar3(): " << bar3() << std::endl;

    /********************
    可以看到，上面bar1的写法会得到预期之外的结果。这是为什么呢？

    函数bar1()的返回值是临时变量
    在调用完bar1()后，它的返回值会立即被释放
    释放后，tmp就变成一个野指针了
    为什么bar0是正常的？

    foo()返回的临时变量的生命周期是在分号之前，它是有效的
    为什么bar2是正常的？

    foo()返回的临时变量已赋值拷贝给foo_copy了
    foo_copy的生命周期则是在bar2结束前
        // 因此，当我们要对函数返回的string值进行c_str()调用时，要注意返回的string的生命周期。如果需要，我们可以赋值拷贝给另外的变量，来延长它的生命周期。
    */
}