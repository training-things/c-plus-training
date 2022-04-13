#include <iostream>
 
struct type
{
    int i;
 
    type(): i(3) {}
 
    void f(int v) const {
        // this->i = v;                 // 编译错误：this 是指向 const 的指针
        const_cast<type*>(this)->i = v; // 只要该对象不是 const 就 OK
    }
};
 
int main() 
{
    int i = 3;                 // 不声明 i 为 const
    const int& rci = i; 
    const_cast<int&>(rci) = 4; // OK：修改 i
    std::cout << "i = " << i << '\n';
 
    type t; // 如果这是 const type t，那么 t.f(4) 会是未定义行为
    t.f(4);
    std::cout << "type::i = " << t.i << '\n';
 
    const int j = 3; // 声明 j 为 const
    [[maybe_unused]]
    int* pj = const_cast<int*>(&j);
    // *pj = 4;      // 未定义行为
 
    [[maybe_unused]] // TODO: 这个是什么意思？ https://stackoverflow.com/questions/49320810/when-should-i-use-maybe-unused
    void (type::* pmf)(int) const = &type::f; // 指向成员函数的指针
    // const_cast<void(type::*)(int)>(pmf);   // 编译错误：const_cast 不能用于成员函数指针
}