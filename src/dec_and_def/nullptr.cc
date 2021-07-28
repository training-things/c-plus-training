#include <iostream>

using namespace std;

class RecordKey
{
public:
    RecordKey(const std::string& key) : _key(key){};
    RecordKey(const std::string&& key) : _key(key){};

private:
    const std::string _key;
};

int main()
{
    auto p = std::unique_ptr<RecordKey>(nullptr);

    cout << "p val = " << p << endl;
    cout << "p ptr = " << &p << endl;

    const std::string k1 = "p1";

    const char *k2 = "p1";

    cout << "k1 val = " << k1 << endl;

    // auto p1 = std::unique_ptr<RecordKey>(k2); // no matching conversion for functional-style cast from 'const std::string' 
    // auto p1 = std::unique_ptr<RecordKey>(new RecordKey(k2)); 
    // c++ 14 可以使用 
    auto p1 = std::make_unique<RecordKey>(k2); 

    cout << "p1 val = " << p1 << endl;
    cout << "p1 ptr = " << &p1 << endl;
}