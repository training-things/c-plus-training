#include <iostream>

using namespace std;

class Shape
{
protected:
    int width, height;

public:
    Shape(int a = 0, int b = 0)
    {
        width = a;
        height = b;
    }

    virtual int area()
    {
        cout << "Parent class area : " << endl;

        return 0;
    }

    /*
         //   int area()
        Parent class area : 
        Parent class area : 

        //  virtual int area()
        Rectangle class area : 
        Triangle class area : 
    */
};

class Rectangle : public Shape
{
public:
    Rectangle(int a = 0, int b = 9) : Shape(a, b) {}

    int area()
    {
        cout << "Rectangle class area : " << endl;

        return (width * height);
    }
};

class Triangle : public Shape
{
public:
    Triangle(int a = 0, int b = 0) : Shape(a, b) {}

    int area()
    {
        cout << "Triangle class area : " << endl;

        return (width * height / 2);
    }
};

int main()
{
    Shape *shape;
    Rectangle rec(10, 20);

    Triangle tri(10, 5);

    shape = &rec;          // store the adress of Rectangle
    int r = shape->area(); // call rectangle area
    cout << "Rectangle area result : " << r << endl;

    shape = &tri;          // store the adress of Triangle
    int t = shape->area(); // call triangle area
    cout << "Triangle area result : " << t << endl;
    return 0;

    /* 
        Rectangle class area : 
        Rectangle area result : 200
        Triangle class area : 
        Triangle area result : 25
    */
}