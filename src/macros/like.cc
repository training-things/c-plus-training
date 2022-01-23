#include <stdio.h>
#include <stdlib.h>

#define likely(x) __builtin_expect(!!(x), 1) //gcc内置函数, 帮助编译器分支优化
#define unlikely(x) __builtin_expect(!!(x), 0)

int main(int argc, char *argv[])
{
    int x = 0;
    x = atoi(argv[1]);

    if (unlikely(x == 3))
    { //告诉编译器这个分支非常不可能为true
        x = x + 9;
    }
    else if (likely(x == 10))
    {
        x = x = 10;
    }
    else
    {
        x = x - 8;
    }

    printf("x=%d\n", x);

    return 0;
}