#include <iostream>

int main()
{
#ifdef USE_HDFS
    printf("setting USE_HDFS \n");
#else
    printf("not setting USE_HDFS \n");
#endif
}
