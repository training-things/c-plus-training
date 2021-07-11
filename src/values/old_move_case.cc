#include <iostream>

/**
 
传统 C++ 通过拷贝构造函数和赋值操作符为类对象设计了拷贝/复制的概念，
但为了实现对资源的移动操作， 调用者必须使用先复制、再析构的方式，否则就需要自己实现移动对象的接口。 

试想，搬家的时候是把家里的东西直接搬到新家去，而不是将所有东西复制一份（重买）再放到新家、 
再把原来的东西全部扔掉（销毁），这是非常反人类的一件事情。

传统的 C++ 没有区分『移动』和『拷贝』的概念，造成了大量的数据拷贝，浪费时间和空间。 
右值引用的出现恰好就解决了这两个概念的混淆问题，例如：
 */

class A
{
public:
    int *pointer;
    A() : pointer(new int(1))
    {
        std::cout << "构造" << pointer << std::endl;
    }
    A(A &a) : pointer(new int(*a.pointer))
    {
        std::cout << "拷贝" << pointer << std::endl;
    } // 无意义的对象拷贝
    A(A &&a) : pointer(a.pointer)
    {
        a.pointer = nullptr;
        std::cout << "移动" << pointer << std::endl;
    }
    ~A()
    {
        std::cout << "析构" << pointer << std::endl;
        delete pointer;
    }
};
// 防止编译器优化
A return_rvalue(bool test)
{
    A a, b;
    if (test)
        return a; // 等价于 static_cast<A&&>(a);
    else
        return b; // 等价于 static_cast<A&&>(b);
}
int main()
{
    A obj = return_rvalue(false);
    std::cout << "obj:" << std::endl;
    std::cout << obj.pointer << std::endl;
    std::cout << *obj.pointer << std::endl;
    return 0;
}

/*
构造0x7f8e91d05970
构造0x7f8e91d05980
移动0x7f8e91d05980
析构0x0
析构0x7f8e91d05970
obj:
0x7f8e91d05980
1
析构0x7f8e91d05980
*/