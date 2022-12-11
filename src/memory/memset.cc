
#include <bitset>
#include <climits>
#include <cstring>
#include <iostream>
#include <sys/time.h>

// us
uint64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

int case1()
{
    auto start = now();
    char a[100];
    std::memset(a, 0, sizeof(a));

    auto end = now();
    auto dt = end - start;

    std::cout << "case1 N=" << sizeof(a) << " dt: " << dt << "us" << std::endl;
}

int case2()
{
    auto start = now();
    int s = 1 << 30; // GB
    char a[s];
    std::memset(a, 0, sizeof(a));

    auto end = now();
    auto dt = end - start;

    std::cout << "case2 N=" << sizeof(a) << " dt: " << dt << "us" << std::endl;
}

int main()
{
    case1();
    case2();
}
