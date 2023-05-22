#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <sys/time.h>

std::mutex g_mutex;
std::condition_variable g_cv;
bool g_isReady = false;

// us
uint64_t now_us()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

uint64_t now_ms()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    // 将秒数换算为毫秒数
    auto value = tv.tv_sec * 1000L + tv.tv_usec / 1000L;

    return value;
}

uint64_t now_s()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    auto value = tv.tv_sec;
    return value;
}

static std::mutex cout_mutex;
void print(const std::string &str)
{
    std::unique_lock<std::mutex> lock(cout_mutex);
    std::cout << "time=" << now_s() << "s," << str << std::endl;
}

void ThreadA()
{
    std::unique_lock<std::mutex> lock(g_mutex);
    while (!g_isReady)
    {
        // wait会释放锁，等待其他线程调用notify_one或notify_all
        print("1");
        g_cv.wait(lock);
        print("2");
    }
    print("Thread A has been notified and is running...");
}

void ThreadB()
{
    print("Thread B is running...");
    sleep(3);
    { // 保证更改变量的同步操作处于临界区域
        std::lock_guard<std::mutex> lock(g_mutex);
        // std::unique_lock<std::mutex> lock(g_mutex);
        // do something
        g_isReady = true;
    }                  // 自动解锁，保证锁的及时释放
    g_cv.notify_one(); // 唤醒一条等待线程
    print("Thread B is finished");
}

int main()
{
    // std::thread t3(ThreadB);
    std::thread t1(ThreadA);
    std::thread t2(ThreadB);

    // t3.join();
    t1.join();
    t2.join();

    int64_t now = time(NULL);
    std::cout << "now:" << now << std::endl;

    return 0;
}