#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Box
{
public:
    Box() { std::cout << "default" << endl; }

    Box(int width, int height, int length) : m_width(width), m_height(height), m_length(length)
    {
        std::cout << "int, int, int" << std::endl;
    }

    // copy
    Box(Box &other) : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length)
    {
        std::cout << "copy" << std::endl;
    }

    // move
    Box(Box &&other) : m_width(other.m_width), m_height(other.m_height), m_length(other.m_length)
    {

        m_contents = std::move(other.m_contents);
        std::cout << "move" << std::endl;
    }

    int Volume()
    {
        return m_width * m_height * m_length;
    }

    void AddItem(string item)
    {
        m_contents.push_back(item);
    }

    void PrintContents()
    {
        for (const auto &item : m_contents)
        {
            std::cout << "print m_contents item: " << item << std::endl;
        }
    }

private:
    int m_width{0};
    int m_height{0};
    int m_length{0};
    vector<string> m_contents;
};

Box getBox()
{
    Box b(5, 10, 12);

    b.AddItem("T");
    b.AddItem("X");
    b.AddItem("Y");

    return b;
}

int main()
{
    Box b;     // default
    Box b1(b); // copy

    Box b2(getBox()); // move

    b2.PrintContents(); // print that we hava all the values

    return 0;
}