#include <vector>
#include <iostream>

int N = 10000;

void rtn1(std::vector<std::string> values)
{

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901..663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";

    for (int i = 0; i < N; ++i)
    {
        values.push_back(std::move(arg + " " + std::to_string(i)));
    }
}

void rtn2(std::vector<std::string> values)
{
    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901..663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";

    for (int i = 0; i < N; ++i)
    {
        values.push_back(std::move(arg + " " + std::to_string(i)));
    }

    values.resize(100);
}

int main(int argc, char **argv)
{
    auto start = clock();
    std::vector<std::string> values1;
    values1.reserve(N);

    rtn1(values1);

    auto end1 = clock();

    std::vector<std::string> values2;
    values2.reserve(N);
    rtn2(values2);

    auto end2 = clock();

    auto dt1 = end1 - start;
    auto dt2 = end2 - end1;

    std::cout << "case1 dt1: " << (double)dt1 / 1000 << "ms" << std::endl;
    std::cout << "case1 dt2: " << (double)dt2 / 1000 << "ms" << std::endl;
}