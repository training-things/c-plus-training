// MemoryBlock.h
#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class MemoryBlock
{
public:
    // Simple constructor that initializes the resource.
    explicit MemoryBlock(size_t length)
        : _length(length), _data(new int[length])
    {
        std::cout << "In MemoryBlock(size_t). length = "
                  << _length << "." << std::endl;
    }

    // Destructor.
    ~MemoryBlock()
    {
        std::cout << "In ~MemoryBlock(). length = "
                  << _length << ".";

        if (_data != nullptr)
        {
            std::cout << " Deleting resource.";
            // Delete the resource.
            delete[] _data;
        }

        std::cout << std::endl;
    }

    // 方案一：
    // Move constructor.
    /*
    MemoryBlock(MemoryBlock &&other) noexcept : _data(nullptr), _length(0)
    {
        std::cout << "In MemoryBlock(MemoryBlock&&). length = "
                  << other._length << ". Moving resource." << std::endl;

        // Copy the data pointer and its length from the
        // source object.
        _data = other._data;
        _length = other._length;

        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other._data = nullptr;
        other._length = 0;
    }
    */

    // 方案二：可靠编程  Robust Programming
    // 如果为你的类同时提供了移动构造函数和移动赋值运算符，则可以编写移动构造函数来调用移动赋值运算符，从而消除冗余代码。 以下示例显示了调用移动赋值运算符的移动构造函数的修改后的版本：
    // Move constructor.
    MemoryBlock(MemoryBlock&& other) noexcept : _data(nullptr)    , _length(0)
    {
        std::cout << "In MemoryBlock(MemoryBlock&&). length = "
                  << other._length << ". Moving resource." << std::endl;

        *this = std::move(other);
    }

    // Move assignment operator.
    MemoryBlock &operator=(MemoryBlock &&other) noexcept
    {
        std::cout << "In operator=(MemoryBlock&&). length = "
                  << other._length << "." << std::endl;

        if (this != &other)
        {
            // Free the existing resource.
            delete[] _data;

            // Copy the data pointer and its length from the
            // source object.
            _data = other._data;
            _length = other._length;

            // Release the data pointer from the source object so that
            // the destructor does not free the memory multiple times.
            other._data = nullptr;
            other._length = 0;
        }
        return *this;
    }

    // Retrieves the length of the data resource.
    size_t Length() const
    {
        return _length;
    }

private:
    size_t _length; // The length of the resource.
    int *_data;     // The resource.
};

int main()
{
    // Create a vector object and add a few elements to it.
    vector<MemoryBlock> v;
    v.push_back(MemoryBlock(25));

    cout << "push 25 end.\n";

    v.push_back(MemoryBlock(75));

    cout << "push 75 end.\n";

    // Insert a new element into the second position of the vector.
    v.insert(v.begin() + 1, MemoryBlock(50));

    cout << "push 50 end.\n";
}

/*
In MemoryBlock(size_t). length = 25.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
push 25 end.
In MemoryBlock(size_t). length = 75.
In MemoryBlock(MemoryBlock&&). length = 75. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.
push 75 end.
In MemoryBlock(size_t). length = 50.
In MemoryBlock(MemoryBlock&&). length = 50. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 25. Moving resource.
In MemoryBlock(MemoryBlock&&). length = 75. Moving resource.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.
In ~MemoryBlock(). length = 0.
push 50 end.
In ~MemoryBlock(). length = 75. Deleting resource.
In ~MemoryBlock(). length = 50. Deleting resource.
In ~MemoryBlock(). length = 25. Deleting resource.
*/