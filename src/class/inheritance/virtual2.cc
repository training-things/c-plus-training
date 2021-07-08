// deriv_VirtualFunctions2.cpp
// compile with: /EHsc
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void NameOf(); // Virtual function.
    void InvokingClass();  // Nonvirtual function.
};

// Implement the two functions.
void Base::NameOf()
{
    cout << "Base::NameOf\n";
}

void Base::InvokingClass()
{
    cout << "Invoked by Base\n";
}

class Derived : public Base
{
public:
    void NameOf();        // Virtual function.
    void InvokingClass(); // Nonvirtual function.
};

// Implement the two functions.
void Derived::NameOf()
{
    cout << "Derived::NameOf\n";
}

void Derived::InvokingClass()
{
    cout << "Invoked by Derived\n";
}

int main()
{
    // Declare an object of type Derived.
    Derived aDerived;

    // Declare two pointers, one of type Derived * and the other
    //  of type Base *, and initialize them to point to aDerived.
    Derived *pDerived = &aDerived;
    Base *pBase = &aDerived;

    // Call the functions.
    pBase->NameOf();           // Call virtual function.
    pBase->InvokingClass();    // Call nonvirtual function.
    pDerived->NameOf();        // Call virtual function.
    pDerived->InvokingClass(); // Call nonvirtual function.
}


/*
Derived::NameOf // 请注意，无论 NameOf 函数是通过指向 Base 的指针还是通过指向 Derived 的指针进行调用，它都会调用 Derived 的函数。 它调用 Derived 的函数，因为 NameOf 是虚函数，并且 pBase 和 pDerived 都指向类型 Derived 的对象。 
Invoked by Base
Derived::NameOf
Invoked by Derived
*/