#include <stdio.h>

void f(unsigned char v)
{

    char c = v;

    unsigned char uc = v;

    unsigned int a = c, b = uc;

    int i = c, j = uc;

    printf("----------------\n");
    // https://www.freecodecamp.org/news/format-specifiers-in-c/

    printf("%%c: %c, %c\n", c, uc); // a single character
    printf("%%X: %X, %X\n", c, uc); // %x or %X a hexadecimal (base 16) integer
    printf("%%u: %u, %u\n", a, b);  // int unsigned decimal
    printf("%%d: %d, %d\n", i, j); // a decimal integer (assumes base 10)
}

int main(int argc, char *argv[])
{

    f(0x80); // 128
    f(0x7F); // 127

    return 0;
}