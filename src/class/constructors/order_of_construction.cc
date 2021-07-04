#include <iostream>

using namespace std;

class C1
{

public:
    C1() { cout << "C1 ctor\n"; }
};

class C2
{

public:
    C2() { cout << "C2 ctor\n"; }
};

class C3
{

public:
    C3() { cout << "C3 ctor\n"; }
};

class BaseContainer
{

public:
    BaseContainer()
    {
        cout << "BaseContainer ctor\n";
    }

private:
    C1 c1;
    C2 c2;
};

class DerivedContainer : public BaseContainer
{
public:
    DerivedContainer() : BaseContainer()
    {
        cout << "DerivedContainer ctor\n";
    }

private:
    C3 c3;
};

int main()
{
    DerivedContainer dc;

    return 0;
}

/*
C1 ctor
C2 ctor
BaseContainer ctor
C3 ctor
DerivedContainer ctor
*/