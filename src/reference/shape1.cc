
#include <stdio.h>
#include <iostream>
// #include <utility>  // std::move

using namespace std;

class shape
{
public:
    virtual ~shape() {}
};

class circle : public shape
{
public:
    circle() { puts("circle()"); }
    ~circle() { puts("~circle()"); }
};

class triangle : public shape
{
public:
    triangle() { puts("triangle()"); }
    ~triangle() { puts("~triangle()"); }
};

class result
{
public:
    result() { puts("result()"); }
    ~result() { puts("~result()"); }
};

result process_shape(const shape &shape1,
                     const shape &shape2)
{
    puts("process_shape()");
    return result();
}

int case1()
{
    puts("main()-case1");
    process_shape(circle(), triangle());
    puts("something else--case1");
}

int case2()
{
    puts("main()-case2");
    // process_shape(circle(), triangle());
    // 如果一个 prvalue 被绑定到一个引用上，它的生命周期则会延长到跟这个引用变量一样长。
    result &&r = process_shape(circle(), triangle());
    puts("something else--case2");
}

int case3()
{
    puts("main()-case3");
    result &&r = std::move(process_shape(circle(), triangle()));
    puts("something else--case3");
}

int main()
{
    // case1();
    // case2();
    case3();
}

/*
case1 output:

main()-case1
circle()
triangle()
process_shape()
result()
~result()
~triangle()
~circle()
something else--case1
*/

/*
case2 output:

main()-case2
circle()
triangle()
process_shape()
result()
~triangle()
~circle()
something else--case2
~result()
*/

/*
case3 output:

main()-case3
circle()
triangle()
process_shape()
result()
~result()
~triangle()
~circle()
something else--case3
*/