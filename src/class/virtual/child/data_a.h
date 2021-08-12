#include "../base.h"

class DataA : public Base
{
private:
    /* dataA */
public:
    DataA(/* args */);
    virtual ~DataA()
    {
        std::cout << "virtual ~DataA()" << std::endl;
    };
};
