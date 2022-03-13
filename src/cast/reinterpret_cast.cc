#include <iostream>

typedef void (*fnptr)();

struct Person
{
  std::string name;
  std::string age;

  std::string toString() const { return name + " " + age; }
};

static void *EncodeValue(uintptr_t v)
{
  return reinterpret_cast<void *>(v);
}
static int DecodeValue(void *v)
{
  return static_cast<int>(reinterpret_cast<uintptr_t>(v));
}

static void *EncodePersonValue(Person *v) { return reinterpret_cast<void *>(v); }
static Person *DecodePersonValue(void *v)
{
  return static_cast<Person *>(reinterpret_cast<Person *>(v));
}

int castInt()
{
  auto d1 = EncodeValue(11);
  auto r1 = DecodeValue(d1);

  std::cout << "d1:" << d1 << ", r1:" << r1 << std::endl;

  auto d2 = EncodeValue(-1);
  auto r2 = DecodeValue(d2);

  std::cout << "d2:" << d2 << ", r2:" << r2 << std::endl;
}

int castPersonStruct()
{

  Person p{"person", "12"};

  auto d1 = EncodePersonValue(&p);
  auto r1 = DecodePersonValue(d1);

  std::cout << "d1:" << d1 << ", r1:" << r1->toString() << std::endl;
}

int main(int argc, char **argv)
{
  castInt();
  castPersonStruct();
}