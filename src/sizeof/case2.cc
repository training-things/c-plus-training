#include <iostream>

typedef struct redisObject
{
    unsigned type : 4;     // redisObject的数据类型，4个bits
    unsigned encoding : 4; // redisObject的编码类型，4个bits
    unsigned lru : 24;     // redisObject的LRU时间，LRU_BITS为24个bits
    int refcount;          // redisObject的引用计数，4个字节
    void *ptr;             //指向值的指针，8个字节
} robj;
// (4 + 4 + 24) / 8 + 4 + 8 

int main()
{
    std::cout << "redisObject sizeof " << sizeof(redisObject) << std::endl; // redisObject sizeof 16
}
