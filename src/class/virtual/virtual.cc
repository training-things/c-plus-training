// #include <iostream>
// #include <memory>

// class Base
// {
// private:
//     /* data */
//     std::string _db;

// public:
//     explicit Base(const std::string &db);
//     virtual ~Base() = default;
// };

// Base::Base(const std::string &db) : _db(db)
// {
//     std::cout << "db " << db << std::endl;
// }

// class DataA : public Base
// {
// private:
//     /* dataA */
// public:
//     DataA(/* args */);
//     virtual ~DataA()
//     {
//         std::cout << "virtual ~DataA()" << std::endl;
//     };
// };

// DataA::DataA(/* args */) : Base("db_name")
// {
//     std::cout << "DataA::DataA" << std::endl;
// }

// int main()
// {
//     auto _ptr = std::unique_ptr<DataA>(new DataA());

//     std::cout << _ptr << std::endl;
// }