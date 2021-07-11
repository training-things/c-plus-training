#include <stdio.h>

struct S
{
    /* data */
    short i;
};

int main()
{
    S s;
    S &sref = s;

    s.i = 3;
    printf("%d\n", s.i);
    printf("%d\n", sref.i);

    sref.i = 5;
    printf("%d\n", s.i);
    printf("%d\n", sref.i);
}

/*
3
3
5
5
*/
