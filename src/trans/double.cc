#include <iostream>

#include <sstream>

// cstdlib is needed for atoi()
// #include <cstdlib>
#include <string>
#include <limits>
#include <iomanip>




std::string dtos1(double a) {
    std::stringstream ss;
    // ss << std::setprecision(15) << a;

    ss << std::setprecision(std::numeric_limits<double>::digits10 + 1) << a;

    return ss.str(); 
}

std::string dtos2(double a) {
    std::stringstream ss;
    ss << a;

    return ss.str(); 
}

typedef std::numeric_limits< double > dbl;

int main() {

    double d = 3.1415926535897912121812;
    std::cout.precision(dbl::max_digits10);
    std::cout << "Pi: " << d << std::endl;


    // declaring and initializing character array
    char cstr1[] = "123.4567123456432";
    char cstr2[] = "81.4567";

    std::string str2 = "123.456732313487231223";
    std::string str3 = "85.456732";

    double num_double1 = std::atof(cstr1);
    double num_double2 = std::atof(cstr2);

    double num_double_stod_2 = std::stod(str2);
    double num_double_stod_3 = std::stod(str3);

    std::cout << std::setprecision(17) << "num_double1 = " << num_double1 << std::endl;
    std::cout << std::setprecision(17) << "num_double2 = " << num_double2 << std::endl;

    std::cout << std::setprecision(17) << "num_double_stod_2 = "  << num_double_stod_2 << std::endl;
    std::cout << std::setprecision(17) << "num_double_stod_3 = "  << num_double_stod_3 << std::endl;
    


    double d1 = 123.456732313487241121213121;
    double d2 = 123.45673;
    double d3 = 13.47;
    double d4 = 85.456732;


    std::cout << "d1 = " << dtos1(d1) << std::endl;
    std::cout << "d2 = " << dtos1(d2) << std::endl;
    std::cout << "d3 = " << dtos1(d3) << std::endl;
    std::cout << "d4 = " << dtos1(d4) << std::endl;

    std::cout << "d1 = " << dtos2(d1) << std::endl;
    std::cout << "d2 = " << dtos2(d2) << std::endl;
    std::cout << "d3 = " << dtos2(d3) << std::endl;
    std::cout << "d4 = " << dtos2(d4) << std::endl;


    return 0;
}

