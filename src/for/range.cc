#include <iostream>

enum class ColumnFamilyNumber : std::uint32_t
{
    ColumnFamily_Default = 0,
    ColumnFamily_Ttl = 1,
    ColumnFamily_String = 2,
    ColumnFamily_HashSet = 3,
    ColumnFamily_ZSet = 4,
    ColumnFamily_List = 5,
    ColumnFamily_Set = 6,
    ColumnFamily_Max
};

ColumnFamilyNumber operator++(ColumnFamilyNumber &x)
{
    return x = (ColumnFamilyNumber)(std::underlying_type<ColumnFamilyNumber>::type(x) + 1);
}

ColumnFamilyNumber operator*(ColumnFamilyNumber c) { return c; }

ColumnFamilyNumber begin(ColumnFamilyNumber r)
{
    return ColumnFamilyNumber::ColumnFamily_Default;
}

ColumnFamilyNumber end(ColumnFamilyNumber r)
{
    ColumnFamilyNumber l = ColumnFamilyNumber::ColumnFamily_Max;
    return ++l;
}

std::ostream &operator<<(std::ostream &o, ColumnFamilyNumber x)
{
    return o << std::underlying_type<ColumnFamilyNumber>::type(x);
}

int main()
{

    for (const auto &cf : ColumnFamilyNumber())
    {
        std::cout << "cf: " << cf << std::endl;
    }

    std::cout << "second: "  << std::endl;
    for (uint32_t i = 0; static_cast<ColumnFamilyNumber>(i) < ColumnFamilyNumber::ColumnFamily_Max; ++i)
    {
        std::cout << "cf: " << static_cast<ColumnFamilyNumber>(i)  << std::endl;
    }

    ColumnFamilyNumber cf1 = ColumnFamilyNumber::ColumnFamily_Max;

    std::cout << "cf1 value: " << (int)cf1 << std::endl;

}
