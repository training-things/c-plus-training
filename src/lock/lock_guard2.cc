#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>

std::mutex my_lock;

void add(int &num, int &sum)
{
    while (true)
    {
        std::lock_guard<std::mutex> lock(my_lock);
        if (num < 100)
        { //运行条件
            num += 1;
            sum += num;
        }
        else
        { //退出条件
            break;
        }
    }
}

int main()
{
    int sum = 0;
    int num = 0;
    std::vector<std::thread> ver; //保存线程的vector
    for (int i = 0; i < 20; ++i)
    {
        std::thread t = std::thread(add, std::ref(num), std::ref(sum));
        ver.emplace_back(std::move(t)); //保存线程
    }

    std::for_each(ver.begin(), ver.end(), std::mem_fn(&std::thread::join)); //join
    std::cout << sum << std::endl;
}

/*

1.std::lock_guard 在构造函数中进行加锁，析构函数中进行解锁。
2.锁在多线程编程中，使用较多，因此c++11提供了lock_guard模板类；在实际编程中，我们也可以根据自己的场景编写resource_guard RAII类，避免忘掉释放资源。

*/