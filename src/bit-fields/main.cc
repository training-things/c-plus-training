#include <iostream>

using namespace std;


// bit fields 类和结构可包含比整型类型占用更少存储空间的成员。 这些成员被指定为位域。 位字段 成员声明符 的语法如下所示：
struct staff
{
    /* data */
    unsigned int field1 : 30;
    unsigned int : 2;
    unsigned int field2 : 2;
    unsigned int : 0;
    unsigned int field3 : 4;
};

// todo
int main()
{
    struct staff s = {1, 3, 5};

    cout << s.field1 << endl;
    cout << s.field2 << endl;
    cout << s.field3 << endl;

    cout << "staff struct sizeof: " << sizeof(s) << endl;

    return 0;
}