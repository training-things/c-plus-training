#include <iostream>
#include <mutex>
#include <thread>
#include <math.h>
#include <vector>



using namespace std;

static const int MAX = 10e8;
static double sum = 0;

static mutex exclusive;

void concurrent_worker1(int min, int max)
{
    for (int i = min; i <= max; i++)
    {
        exclusive.lock(); // ①
        sum += sqrt(i);
        exclusive.unlock(); // ②
    }
}


void concurrent_worker2(int min, int max) {
  double tmp_sum = 0;
  for (int i = min; i <= max; i++) {
    tmp_sum += sqrt(i); // ①
  }
  exclusive.lock(); // ②
  sum += tmp_sum;
  exclusive.unlock();
}


void concurrent_task(int min, int max)
{
    auto start_time = chrono::steady_clock::now();

    unsigned concurrent_count = thread::hardware_concurrency();
    cout << "hardware_concurrency: " << concurrent_count << endl;
    vector<thread> threads;
    min = 0;
    sum = 0;
    for (int t = 0; t < concurrent_count; t++)
    {
        int range = max / concurrent_count * (t + 1);
        threads.push_back(thread(concurrent_worker1, min, range)); // ③
        min = range + 1;
    }

    cout << "threads.size(): " << threads.size() << endl;

    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    auto end_time = chrono::steady_clock::now();
    auto ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Concurrent task finish, " << ms << " ms consumed, Result: " << sum << endl;
}


int main()
{
    concurrent_task(1, 100000000);
}

/*
output
concurrent_worker1:
hardware_concurrency: 8
threads.size(): 8
Concurrent task finish, 12751 ms consumed, Result: 6.66667e+11


concurrent_worker2:
hardware_concurrency: 8
threads.size(): 8
Concurrent task finish, 122 ms consumed, Result: 6.66667e+11
*/

/*
在访问共享数据之前加锁
访问完成之后解锁
在多线程中使用带锁的版本
*/