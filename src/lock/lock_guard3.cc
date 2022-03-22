#include <iostream>
#include <string>
#include <mutex>

#include <unistd.h>
#include <pthread.h>

#include <chrono>
#include <ctime>
#include <thread>

class spin_lock
{
public:
    spin_lock()
    {
        pthread_spin_init(&lock_, 0);
    }
    ~spin_lock()
    {
        pthread_spin_destroy(&lock_);
    }
    spin_lock(const spin_lock &) = delete;

    void lock()
    {
        pthread_spin_lock(&lock_);
    }
    void unlock()
    {
        pthread_spin_unlock(&lock_);
    }

private:
    pthread_spinlock_t lock_;
};

std::string timeToString(std::chrono::system_clock::time_point &t)
{
    std::time_t time = std::chrono::system_clock::to_time_t(t);
    std::string time_str = std::ctime(&time);
    time_str.resize(time_str.size() - 1);
    return time_str;
}

void printLog(const std::string &log)
{
    auto now = std::chrono::system_clock::now();
    std::cout << timeToString(now) << " " << log << std::endl;
}

class Sp
{
public:
    Sp(){};
    Sp(const Sp &){};
    void f1()
    {
        printLog("f1: starting");
        std::lock_guard<spin_lock> guard(spin_lock_);
        printLog("f1: start sleep");
        sleep(10);
        printLog("f1: end");
    }

    void f2()
    {
        printLog("f2: starting");
        printLog("f2: start sleep");
        sleep(2);
        printLog("f2: sleep end");

        std::lock_guard<spin_lock> guard(spin_lock_);
        printLog("f2: end");
    }

private:
    mutable spin_lock spin_lock_;
};

void case1()
{
    printLog("case1");
    Sp sp{};
    // Sp sp = Sp();
    sp.f1();
    sp.f2();

    /********************************
        Tue Mar 22 10:56:24 2022 case1
        Tue Mar 22 10:56:24 2022 f1: starting
        Tue Mar 22 10:56:24 2022 f1: start sleep
        Tue Mar 22 10:56:34 2022 f1: end
        Tue Mar 22 10:56:34 2022 f2: starting
        Tue Mar 22 10:56:34 2022 f2: start sleep
        Tue Mar 22 10:56:36 2022 f2: sleep end
        Tue Mar 22 10:56:36 2022 f2: end
     */
}
Sp sp2{};
void multiThreaded(int id)
{
    printLog("multiThreaded, id: " + std::to_string(id));
    
    if (id == 1)
    {
        sp2.f1();
    }
    else if (id == 2)
    {
        sp2.f2();
    }
}

void case2()
{
    printLog("case2");
    std::thread t1(multiThreaded, 1);
    std::thread t2(multiThreaded, 2);
    t1.join();
    t2.join();
    /********************************
    Tue Mar 22 11:01:32 2022 case2
    Tue Mar 22 11:01:32 2022 multiThreaded, id: 2
    Tue Mar 22 11:01:32 2022 multiThreaded, id: 1
    Tue Mar 22 11:01:32 2022 f2: starting
    Tue Mar 22 11:01:32 2022 f1: starting
    Tue Mar 22 11:01:32 2022 f2: start sleep
    Tue Mar 22 11:01:32 2022 f1: start sleep
    Tue Mar 22 11:01:34 2022 f2: sleep end
    Tue Mar 22 11:01:42 2022 f1: end
    Tue Mar 22 11:01:42 2022 f2: end
    */
}

int main()
{
    case1();
    case2();
}
