#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <sstream>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include <cmath>
#include <algorithm>
#include <regex>

#include "string_view.h"



// us
uint64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

std::vector<std::string> SplitStringDelim(const std::string &arg,
                                          const std::string &delim)
{
    std::vector<std::string> splits;

    splits.reserve(4);

    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.emplace_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.emplace_back(arg.substr(beg));

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

std::vector<nonstd::string_view> SplitStringDelim6(const std::string &arg,
                                          const std::string &delim)
{
    std::vector<nonstd::string_view> splits;

    splits.reserve(4);

    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.emplace_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.emplace_back(arg.substr(beg));

    return splits;
}


std::vector<std::string> SplitStringDelim7(const std::string &str, const std::string &pattern)
{
    char * strc = new char[strlen(str.c_str())+1];
    strcpy(strc, str.c_str());   //string转换成C-string
    std::vector<std::string> res;
    res.reserve(4);
    char* temp = strtok(strc, pattern.c_str());
    while(temp != NULL)
    {
        res.push_back(temp);
        temp = strtok(NULL, pattern.c_str());
    }
    delete[] strc;
    return res;
}


std::vector<std::string> SplitStringDelim8(const std::string &str, const std::string &pattern)
{
    std::regex re(pattern);

    std::vector<std::string> res(std::sregex_token_iterator(str.begin(), str.end(),re, -1), std::sregex_token_iterator());

    return res;
}

void case1(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim(arg, "&&");
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case1 dt: " << dt  << "us" << std::endl;
}

void case2(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        splits.reserve(4);
        SplitStringDelim2(arg, "&&", splits);
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case2 dt: " << dt  << "us" << std::endl;
}

void case3(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        auto res = SplitStringDelim3(arg, '&');
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case3 dt: " << dt  << "us" << std::endl;
}

void case4(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        std::vector<std::string> splits;
        splits.reserve(4);
        SplitStringDelim4(arg, '&', splits);
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case4 dt: " << dt  << "us" << std::endl;
}

void case5(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim5(arg, "&&");
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case5 dt: " << dt  << "us" << std::endl;
}

void case6(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim6(arg, "&&");
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case6 dt: " << dt  << "us" << std::endl;
}

void case7(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim7(arg, "&&");
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case7 dt: " << dt  << "us" << std::endl;
}


void case8(size_t N = 1000)
{
    auto start = now();

    std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&27.090602&&114.977901";
    for (size_t i = 0; i < N; i++)
    {
        auto res = SplitStringDelim8(arg, "&&");
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "case8 dt: " << dt  << "us" << std::endl;
}

int main()
{
    size_t N = 10000;
    case1(N);
    case2(N);
    // case3(N); // worse case
    // case4(N); // worse case
    case5(N);

    case6(N);
    // case7(N);
    // case8(N); // worse case case8 dt: 185420us

    /* case
    case1 dt: 4907us
    case2 dt: 5679us
    case5 dt: 5322us
    case6 dt: 2533us
    */
}