#include <iostream>

struct Person
{
    std::string name;
    int age;
    std::string address;
};

static void *EncodePerson(Person *v)
{
    // return reinterpret_cast<void *>(v); // case1 ok
    return static_cast<void *>(v); // case2 ok
}

static Person *DecodePerson(void *v)
{
    // return static_cast<Person *>(reinterpret_cast<Person *>(v)); case1 ok 
    // return reinterpret_cast<Person *>(v); // case1 ok
    return static_cast<Person *>(v); // case2 ok
}

Person p{"aierui", 25, "Beijing"};

void test1()
{
    std::cout << "Person(p) pointer: " << (void *)&p << std::endl;
}

void test2()
{
    auto ptr = EncodePerson(&p);
    auto ptrVal = DecodePerson(ptr);
    std::cout << "Person(p) pointer: " << ptr << std::endl;
    std::cout << "Person(p) pointerValue.Name: " << ptrVal->name << std::endl;
    std::cout << "Person(p) pointerValue.Age: " << ptrVal->age << std::endl;
    std::cout << "Person(p) pointerValue.Address: " << ptrVal->address << std::endl;
}

 // C++还提供了四种类型转换方法
    /*
        static_cast<类型说明符>(表达式） 转换一个类型为另一相关类型
        dynamic_cast<类型说明符>(表达式） 在继承层级中转换
        const_cast<类型说明符>(表达式） 添加或移除 cv 限定符
        reinterpret_cast<类型说明符>(表达式） 重新诠释的转型 转换类型到无关类型

        这 四个 关键词是 「特殊运算符」中的一部分

     */

    /************************
     cv 是什么？ https://zh.cppreference.com/w/cpp/language/cv
     cv（const 与 volatile）类型限定符
     */

    // static_cast和reinterpret_cast似乎都可以很好地将void*转换为另一种指针类型. 有充分的理由偏爱其中一个吗？


int main()
{
    test1();
    test2();
}

// 表达式 类型转换 https://zh.cppreference.com/w/cpp/language/expressions
// 
/*
## reinterpret_cast 
是 C++ 中使用的一种类型转换运算符。它用于将一个指针转换为任何类型的另一个指针，无论该类是否相互关联。它不检查指针类型和指针指向的数据是否相同。reinterpret_cast 运算符可用于转换，例如 char* 到 int* ，或 One_class* 到 Unrelated_class* ，它们本质上是不安全的.



*/