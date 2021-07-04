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

    display_balance(payable);
    display_balance(49.95);
    display_balance(9.99f);

    return 0;
}

/*

The balance is: 79.99
The balance is: 49.95
The balance is: 9.99


*/