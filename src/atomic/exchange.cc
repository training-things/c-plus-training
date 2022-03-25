#include <iostream>
#include <sys/time.h>
#include <atomic>
#include <string>
#include <stdlib.h>
#include <unistd.h>

// us
uint64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

const constexpr static int kINTERIM = 3 * 1000000; //
static std::atomic<uint64_t> last_execute_time{0};

void case1()
{
    uint64_t start = now();
    uint64_t dup_now = start;
    uint64_t last_time = last_execute_time.exchange(start);

    auto dt = dup_now - last_time;
    

    bool up = false;

    if (dt < kINTERIM)
    {
        up = true;
        last_execute_time.store(last_time);
    }

    std::cout << "up: " << up << " dt: " << dt << "us"
              << " start: " << start << " last_time: " << last_time << std::endl;
}

int main()
{

    case1();
    sleep(2);
    case1();
    sleep(2);
    case1();
    sleep(5);
    case1();
    case1();
    sleep(5);
    case1();
    sleep(5);
    case1();
}