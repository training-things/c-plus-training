#include <iostream>
#include <random>
#include <string>
#include <iostream>

#include "benchmark/benchmark.h"

class Command
{
public:
    Command(int n, const std::string &str) : n_(n), m_(n), s_(str){};
    ~Command(){};

    void bar()
    {
        m_ += 1;
    }
    static int foo(int n)
    {
        n += 1;
        return n;
    }

private:
    int n_ = 0;
    int m_ = 0;
    std::string s_ = "";
};

static void BM_Constructor(benchmark::State &state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        // benchmark::DoNotOptimize();
        Command command = Command(0, "a1");
        command.bar();
        state.ResumeTiming();
    };
}

BENCHMARK(BM_Constructor)
    ->DenseRange(10, 11)
    //    ->Threads(20)
    ->Unit(benchmark::kMicrosecond);

static void BM_StaticMethod(benchmark::State &state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Command::foo(1);
        state.ResumeTiming();
    };
}

BENCHMARK(BM_StaticMethod)
    ->DenseRange(10, 11)
    //    ->Threads(20)
    ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
