#include <cstdio>

struct A1
{
    virtual ~A1() { printf("A1 dtor\n"); }
};
struct A2 : A1
{
    virtual ~A2() { printf("A2 dtor\n"); }
};
struct A3 : A2
{
    virtual ~A3() { printf("A3 dtor\n"); }
};

struct B1
{
    ~B1() { printf("B1 dtor\n"); }
};
struct B2 : B1
{
    ~B2() { printf("B2 dtor\n"); }
};
struct B3 : B2
{
    ~B3() { printf("B3 dtor\n"); }
};

int main()
{
    A1 *a = new A3;
    delete a;
    printf("\n");

    B1 *b = new B3;
    delete b;
    printf("\n");

    B3 *b2 = new B3;
    delete b2;
}

/*

A3 dtor
A2 dtor
A1 dtor

B1 dtor

B3 dtor
B2 dtor
B1 dtor

*/