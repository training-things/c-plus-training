#include <string>
#include <iostream>

using namespace std;

struct returning_multiple_values_case1
{
    /* data */
    string name;
    int num;
};

returning_multiple_values_case1 g()
{
    // string t{"hello"}; // error: expected ';' at end of declaration
    // int u{43};

    string t = "hello";
    int u = 43;

    return {t, u}; //  warning: generalized initializer lists are a C++11 extension [-Wc++11-extensions]

    // return {"hello", 10};
}

int main()
{
    returning_multiple_values_case1 s = g();

    cout << "name: " << s.name << ", num: " << s.num << endl; // name: hello, num: 43

    return 0;
}