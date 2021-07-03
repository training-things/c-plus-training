#include <stdio.h>

// polymorphism in c

typedef void (*pf)();

typedef struct _P
{
    pf _f;
} P;

typedef struct _C
{
    P _c;

} C;

void funcA()
{
    printf("%s\n", "Base P::func()");
}

void funcB()
{
    printf("%s\n", "Derived C::func()");
}

int main()
{
    P a;
    C b;

    a._f = funcA;
    b._c._f = funcB;

    P *pa = &a;
    pa->_f();
    
    pa = (P *)&b;
    pa->_f();

    /*
        Base P::func()
        Derived C::func()
    */
}