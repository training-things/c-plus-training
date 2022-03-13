#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>

size_t N = 10000;

std::vector<std::string> SplitStringDelim(const std::string &arg,
                                          const std::string &delim)
{
    std::vector<std::string> splits;

    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.push_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.push_back(arg.substr(beg));

    return splits;
}

void SplitStringDelim2(const std::string &arg,
                       const std::string &delim, std::vector<std::string> splits)
{
    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.push_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.push_back(arg.substr(beg));
}

std::vector<std::string> SplitStringDelim3(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        // elems.push_back(item);
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    return elems;
}

void SplitStringDelim4(const std::string &s, char delim, std::vector<std::string> elems)
{
    std::stringstream ss(s);
    std::string item;
    // std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        // elems.push_back(item);
        elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
    }
    //   return elems;
}

std::vector<std::string> SplitStringDelim5(const std::string &str, const std::string &delims = " ")
{
    std::vector<std::string> output;
    auto first = std::begin(str);

    while (first != std::end(str))
    {
        const auto second = std::find_first_of(first, std::end(str),
                                               std::begin(delims), std::end(delims));

        if (first != second)
            output.emplace_back(first, second);

        if (second == std::end(str))
            break;

        first = std::next(second);
    }

    return output;
}

void case1()
{
    auto start = clock();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim(arg, "&&");
    }

    auto end = clock();

    auto dt = end - start;

    std::cout << "case1 dt: " << (double)dt / 1000 << "ms" << std::endl;
}

void case2()
{
    auto start = clock();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        splits.reserve(4);
        SplitStringDelim2(arg, "&&", splits);
    }

    auto end = clock();

    auto dt = end - start;

    std::cout << "case2 dt: " << (double)dt / 1000 << "ms" << std::endl;
}

void case3()
{
    auto start = clock();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        auto res = SplitStringDelim3(arg, '&');
    }

    auto end = clock();

    auto dt = end - start;

    std::cout << "case3 dt: " << (double)dt / 1000 << "ms" << std::endl;
}

void case4()
{
    auto start = clock();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        splits.reserve(4);
        SplitStringDelim4(arg, '&', splits);
    }

    auto end = clock();

    auto dt = end - start;

    std::cout << "case4 dt: " << (double)dt / 1000 << "ms" << std::endl;
}

void case5()
{
    auto start = clock();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim5(arg, "&&");
    }

    auto end = clock();

    auto dt = end - start;

    std::cout << "case1 dt: " << (double)dt / 1000 << "ms" << std::endl;
}

int main()
{
    case1();
    case2();
    case3();
    case4();
    case5();
}