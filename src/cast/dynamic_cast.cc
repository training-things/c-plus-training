#include <iostream>

using namespace std;

class MyBase
{
public:
  virtual void test() {}
};
class MyChild : public MyBase
{
};

class MyChild2 : public MyBase
{
  void test() override{};
};

int main()
{

  MyChild *child0 = new MyChild();
  MyBase *base0 = dynamic_cast<MyBase *>(child0);

  cout << "child0 " << child0 << endl;
  cout << "base0 " << base0 << endl;

  MyChild *child = new MyChild();
  MyBase *base1 = dynamic_cast<MyBase *>(child);

  cout << "child " << child << endl;
  cout << "base1 " << base1 << endl;

  MyBase *base2 = new MyBase();
  MyChild *child2 = dynamic_cast<MyChild *>(base2);

  cout << "base2 " << base2 << endl;
  cout << "child2 " << child2 << endl;

  MyBase *base3 = new MyBase();
  MyChild *child3 = static_cast<MyChild *>(base3);
  cout << "base3 " << base3 << endl;
  cout << "child3 " << child3 << endl;

  MyBase *base4 = new MyBase();
  MyChild2 *child4 = dynamic_cast<MyChild2 *>(base4);

  cout << "base4 " << base4 << endl;
  cout << "child4 " << child4 << endl;

  /*
  child0 0x7f9a5e5059d0
  base0 0x7f9a5e5059d0
  child 0x7f9a5e5059e0
  base1 0x7f9a5e5059e0
  base2 0x7f9a5e5059f0
  child2 0x0
  base3 0x7f9a5e505a00
  child3 0x7f9a5e505a00
  base4 0x7f9a5e505a10
  child4 0x0
  */
}