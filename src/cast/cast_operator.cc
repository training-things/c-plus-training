struct X
{
    // 隐式转换
    operator int() const { return 7; }
 
    // 显式转换
    explicit operator int*() const { return nullptr; }
 
    // 错误：转换类型标识中不能出现数组运算符
//  operator int(*)[3]() const { return nullptr; }
 
    using arr_t = int[3];
    operator arr_t*() const { return nullptr; } // 可以通过 typedef 转换
//  operator arr_t () const; // 错误：任何情况下都不能转换到数组
};
 
int main()
{
    X x;
 
    int n = static_cast<int>(x);   // OK：设 n 为 7
    int m = x;                     // OK：设 m 为 7
 
    int* p = static_cast<int*>(x); // OK：设 p 为空
//  int* q = x; // 错误：没有隐式转换
 
    int (*pa)[3] = x;  // OK
}