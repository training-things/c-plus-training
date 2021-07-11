#include <iostream>

using namespace std;

struct Person
{
    char *Name;
    short Age;
};

int main()
{
    Person myFriend;
    Person &rMyF = myFriend;

    myFriend.Name = "bill";
    rMyF.Age = 20;

    cout << rMyF.Name << " is " << myFriend.Age << endl;
}

/*
bill is 20
*/