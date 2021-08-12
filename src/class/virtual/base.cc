#include "base.h"

Base::Base(const std::string &db) : _db(db)
{
    std::cout << "db " << db << std::endl;
}

