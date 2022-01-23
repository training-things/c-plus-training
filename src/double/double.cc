#include <iostream>
#include <string>

using namespace std;

int main() {
    double d1 = 1 / 6356725.0;
    std::cout << "d1=" << d1 << std::endl;



    double d2 = 46.03844546602622;
    std::cout << "d2=" << d2 << std::endl;
    printf("d2=%.14f\n", d2);


    string s1 = "46.03844546602622";
    double s1_d1 = stold(s1);
    printf("d2=%.14f\n", s1_d1);
    printf("d2=%.17g\n", s1_d1);


    char dbuf[128], sbuf[128];
    int dlen, slen;
    dlen = snprintf(dbuf, sizeof(dbuf),"%.14f", d2);
    string d2_str(dbuf, dlen);
    
    std::cout << "d2_str=" << d2_str << std::endl;


    std::cout << "46.03844546602622 = " << 46.03844546602622 << std::endl;

}