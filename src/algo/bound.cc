#include <iostream>
#include <algorithm>
#include <vector>

struct PriceInfo
{
    double price;
};

void t1()
{
    const std::vector<int> data = {1, 2, 4, 5, 5, 6};
    for (int i = 0; i < 8; ++i)
    {
        // Search for first element x such that i ≤ x
        auto lower = std::lower_bound(data.begin(), data.end(), i);

        std::cout << i << " ≤  lower=" << *lower << " ";
        lower != data.end()
            ? std::cout << *lower << " at index " << std::distance(data.begin(), lower)
            : std::cout << "[not found]";
        std::cout << '\n';
    }

    // const std::vector<int> data = { 1, 2, 4, 5, 5, 6 };
    for (int i = 0; i < 7; ++i)
    {
        // Search first element that is greater than i
        auto upper = std::upper_bound(data.begin(), data.end(), i);

        std::cout << i << " < "
                  << " upper=" << *upper << " ";
        upper != data.end()
            ? std::cout << *upper << " at index " << std::distance(data.begin(), upper)
            : std::cout << "not found";
        std::cout << '\n';
    }

    std::vector<PriceInfo> prices = {{100.0}, {101.5}, {102.5}, {102.5}, {107.3}};
    for (double to_find : {102.1, 110.2})
    {
        auto prc_info = std::lower_bound(prices.begin(), prices.end(), to_find,
                                         [](const PriceInfo &info, double value)
                                         {
                                             return info.price < value;
                                         });

        std::cout << "to_find=" << to_find << " ";
        prc_info != prices.end()
            ? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
            : std::cout << to_find << " not found";
        std::cout << '\n';
    }

    std::cout << '\n';
    for (double to_find : {102.1, 110.2})
    {
        auto prc_info = std::upper_bound(prices.begin(), prices.end(), to_find,
                                         [](double value, const PriceInfo &info)
                                         {
                                             return value < info.price;
                                         });

        std::cout << "to_find=" << to_find << " ";
        prc_info != prices.end()
            ? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
            : std::cout << to_find << " not found";
        std::cout << '\n';
    }

    std::cout << '\n';
    for (double to_find : {102.1, 110.2})
    {
        auto prc_info = std::upper_bound(prices.begin(), prices.end(), to_find,
                                         [](double value, const PriceInfo &info)
                                         {
                                             return info.price < value;
                                         });

        std::cout << "to_find=" << to_find << " ";
        prc_info != prices.end()
            ? std::cout << prc_info->price << " at index " << prc_info - prices.begin()
            : std::cout << to_find << " not found";
        std::cout << '\n';
    }
}

void lower()
{

    // std::vector<int> v = {1,2,3,4,5,6,7,8,9};
    // auto it = std::lower_bound(
    //     v.cbegin(),
    //     10,
    //     8,
    //     [](const decltype(v)::val_type &vf, const int a) {
    //         return vf < a;
    // });
}

void upper()
{
}

int main()
{

    t1();

    std::cout << "lower====:" << std::endl;
    lower();
    std::cout << "upper====:" << std::endl;
    upper();

    return 0;
}
