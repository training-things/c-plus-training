#define NDEBUG // ignore assert

#include <assert.h>

int main()
{
    int x = 7;

    assert(x == 5); // exited with code=0 in 0.188 seconds

    return 0;
}