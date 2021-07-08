#include <iostream>

class Money
{
public:
    Money() : amount{0.0} {};
    Money(double _amount) : amount{_amount} {};

    double amount;
};

void display_balance(const Money balance)
{
    std::cout << "The balance is: " << balance.amount << std::endl;
}

int main(int argc, char *argv[])
{
    Money payable{79.99};

    display_balance(payable); // 首次调用（它将采用类型 Money 的自变量）不需要转换，因为它的自变量类型正确。
    display_balance(49.95); // 需要进行转换，因为参数的类型（值为 double 49.95 ）不是函数期望的值。 函数不能直接使用此值，但是由于存在从自变量的类型 double 到匹配参数类型的转换，因此 Money 类型的临时值 Money 是从自变量构造的，用于完成函数调用
    display_balance(9.99f); // 参数不是 double ，而是值为 float 的

    return 0;
}

/*

The balance is: 79.99
The balance is: 49.95
The balance is: 9.99


*/