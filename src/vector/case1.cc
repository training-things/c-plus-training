#include <iostream>
#include <vector>

using mk_t = uint64_t;

enum d_mk_t : mk_t
{
    d_m1,
    d_m2,
    d_m3,
};

class m
{

public:
    m() : a_(0) {}

    m(uint64_t a) : a_(a) {}

    uint64_t a_;
};

int main()
{
    std::cout << "hello world!" << std::endl;

    std::vector<m> m1;
    m1.resize(3);

    m1[d_m1] = m(1);
    m1[d_m2] = m(2);
    m1[d_m3] = m(3);

    for (m item : m1)
    {
        std::cout << "item.a: " << item.a_ << std::endl;
    }
}