#include <iostream>
#include <string>

using namespace std;

class dog
{
public:
    dog()
    {
        _legs = 4;
        _bark = true;
    }

    void setDogSize(string dogSize)
    {
        _dogSize = dogSize;
    }

    virtual void setEars(string type)
    {
        _earType = type;
    }

private:
    string _dogSize, _earType;
    int _legs;
    bool _bark;
};

class breed : public dog
{
private:
    /* data */
protected:
    string _color, _earLength, _earType;

public:
    breed(string color, string size);
    ~breed();

    void setEars(string length, string type);
    string getColor();
};

breed::breed(string color, string size)
{
    _color = color;
    setDogSize(size);
}

breed::~breed()
{
}

void breed::setEars(string length, string type)
{
    _earLength = length;
    _earType = type;
}

string breed::getColor()
{
    return _color;
}

int main()
{
    dog mongrel;
    breed labrador("yellow", "large");
    mongrel.setEars("pointy");
    labrador.setEars("long", "floppy");
    cout << "Cody is a " << labrador.getColor() << " labrador" << endl; // Cody is a yellow labrador
}