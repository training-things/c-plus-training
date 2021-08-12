#include <iostream>
#include <memory>

class Base
{
private:
    /* data */
    std::string _db;

public:
    explicit Base(const std::string &db);
    virtual ~Base() = default;
};
