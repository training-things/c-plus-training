#include <iostream>
#include <sstream>

enum class Role : int8_t
{
    Master,
    Slave,
};

std::ostream &operator<<(std::ostream &os, Role role)
{
    if (role == Role::Master)
    {
        os << "master";
    }
    else if (role == Role::Slave)
    {
        os << "slave";
    }
    else
    {
        os << "";
    }
    return os;
}

int main(){
    auto a = Role::Master;

    std::stringstream ss;
    ss << a;

    std::cout << "Role: " << ss.str() << std::endl;
}

