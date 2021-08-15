#include <iostream>

enum class ColumnFamilyNumber : std::uint32_t
{
    ColumnFamily_Default = 0,
    ColumnFamily_Ttl,
    ColumnFamily_String,
    ColumnFamily_HashSet,
    ColumnFamily_ZSet,
    ColumnFamily_List,
    ColumnFamily_Set,
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
}
