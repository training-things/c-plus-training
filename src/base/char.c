#include <stdio.h>
 
int main()
{
	char a = -1;
	signed char b = -1;
	unsigned char c = -1;
 
	printf("a=%d,b=%d,c=%d\n", a, b, c);
	return 0;

    /* output:
    a=-1,b=-1,c=255

    // 说明我的机器把 char 当成 signed char 处理。

    char与signed char, unsigned char的区别？
    https://blog.csdn.net/sinat_20265495/article/details/51733015
    */
}