#include <iostream>

using namespace std;

int main()
{
    const int a = 1; // note: variable 'a' declared const here

    a = 0; // error: cannot assign to variable 'a' with const-qualified type 'const int'

    const string s = "hello world";

    return 0;
}
