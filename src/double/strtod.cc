#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

std::string ToString(double o)
{
    std::ostringstream os;
    os << std::setprecision(std::numeric_limits<double>::max_digits10) << o;
    return os.str();
}

int main()
{
    std::string str = "29.537932983";

    double l1 = strtod(str.c_str(), NULL);
    double l2 = atof(str.c_str());

    std::cout << "str: " << str << ", strtod: " << l1 << std::endl;
    std::cout << "str: " << str << ", strtod.ToString: " << ToString(l1) << std::endl;
    std::cout << "str: " << str << ", atof: " << l2 << std::endl;
    std::cout << "str: " << str << ", atof.ToString: " << ToString(l2) << std::endl;
}