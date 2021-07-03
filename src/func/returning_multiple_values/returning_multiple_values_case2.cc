#include <tuple>
#include <string>
#include <iostream>

using namespace std;

tuple<int, string, double> f()
{
    int i = 108;
    string s = "Some text";
    double d = 0.1;

    return {i, s, d};
}

//complie:  g++ -Wall -Wextra -std=c++17 -g returning_multiple_values_case2.cc -o returning_multiple_values_case2

int main()
{
    auto t = f();
    cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << endl;

    //
    cout << "The second print: " << endl;
    int myval;
    string myname;
    double mydecimal;
    tie(myval, myname, mydecimal) = f();
    cout << myval << " " << myname << " " << mydecimal << endl;

    return 0;
}