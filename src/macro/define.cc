#include <iostream>
#include <stdio.h>

#define exp(s) printf("exp s is:%s\n", s)
#define exp1(s) printf("exp1 s is:%s\n", #s) // #是“字符串化”的意思，出现在宏定义中的#是把跟在后面的参数转换成一个字符串。
#define exp2(s) #s

// “##”是一种分隔连接方式，它的作用是先分隔，然后进行强制连接。将宏定义的多个形参转换成一个实际参数名。
// 当定义的宏不能用一行表达完整时，可以用”\”表示下一行继续此宏的定义。


int main()
{
    exp("hello");
    exp1(hello);
    exp1("hello");

    std::string str = exp2(bac);
    std::cout << str << " " << str.size() << std::endl;

    std::string str2 = exp2("adadada");
    std::cout << str2 << " " << str2.size() << std::endl;

    /**
     * 忽略传入参数名前面和后面的空格。
     */
    std::string str1 = exp2( asda bac );
    /**
     * 当传入参数名间存在空格时，编译器将会自动连接各个子字符串，
     * 用每个子字符串之间以一个空格连接，忽略剩余空格。
     */
    std::cout << str1 << " " << str1.size() << std::endl;
    return 0;
}

/*

exp s is:hello
exp1 s is:hello
exp1 s is:"hello"
bac 3
"adadada" 9
asda bac 8

*/
