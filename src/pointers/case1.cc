#include <iostream>

int main()
{
    int nums[] = {0, 1, 2, 3, 4, 5};
    size_t len = sizeof(nums) / sizeof(nums[0]);
    int *iter;
    int *end = nums + len; // end 是尾后指针
    for (iter = nums; iter != end; ++iter)
    {
        printf("%d\n", *iter);
    }
}