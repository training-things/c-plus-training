#include <iostream>
#include <random>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <chrono>
#include <tuple>
#include <future>
#include <stdexcept>
#include <sstream>

using namespace std;

// this sets the length of the string we will be using as a key.
// modify this to test whether key complexity changes the performance ratios
// of the various maps
static const size_t key_length = 20;

// the number of keys we will generate (the size of the test)
const size_t nkeys = 1000000;

// the types of map we will test
unordered_map<string, string> unordered;
map<string, string> ordered;
vector<pair<string, string>> flat_map;

// a vector of all keys, which we can shuffle in order to randomise
// access order of all our maps consistently
vector<string> keys;

// use a virtual method to prevent the optimiser from detecting that
// our sink function actually does nothing. otherwise it might skew the test
struct string_user
{
    virtual void sink(const std::string &) = 0;
    virtual ~string_user() = default;
};

struct real_string_user : string_user
{
    virtual void sink(const std::string &) override
    {
    }
};

struct real_string_user_print : string_user
{
    virtual void sink(const std::string &s) override
    {
        cout << s << endl;
    }
};

// generate a sink from a string - this is a runtime operation and therefore
// prevents the optimiser from realising that the sink does nothing
std::unique_ptr<string_user> make_sink(const std::string &name)
{
    if (name == "print")
    {
        return make_unique<real_string_user_print>();
    }
    if (name == "noprint")
    {
        return make_unique<real_string_user>();
    }
    throw logic_error(name);
}

// generate a random key, given a random engine and a distribution
auto gen_string = [](auto &engine, auto &dist)
{
    std::string result(key_length, ' ');
    generate(begin(result), end(result), [&]
             { return dist(engine); });
    return result;
};

// comparison predicate for our flat map.
struct pair_less
{
    bool operator()(const pair<string, string> &l, const string &r) const
    {
        return l.first < r;
    }

    bool operator()(const string &l, const pair<string, string> &r) const
    {
        return l < r.first;
    }
};

int main()
{
    // generate the sink, preventing the optimiser from realising what it
    // does.
    stringstream ss;
    ss << "noprint";
    string arg;
    ss >> arg;
    auto puser = make_sink(arg);

    // generate keys
    auto eng = std::default_random_engine(std::random_device()());
    auto alpha_dist = std::uniform_int_distribution<char>('A', 'Z');

    for (size_t i = 0; i < nkeys; ++i)
    {
        bool inserted = false;
        auto value = to_string(i);
        while (!inserted)
        {
            // generate a key
            auto key = gen_string(eng, alpha_dist);
            // try to store it in the unordered map
            // if it already exists, force a regeneration
            // otherwise also store it in the ordered map and the flat map
            tie(ignore, inserted) = unordered.emplace(key, value);
            if (inserted)
            {
                flat_map.emplace_back(key, value);
                ordered.emplace(key, std::move(value));
                // record the key for later use
                keys.emplace_back(std::move(key));
            }
        }
    }
    // turn our vector 'flat map' into an actual flat map by sorting it by pair.first. This is the key.
    sort(begin(flat_map), end(flat_map),
         [](const auto &l, const auto &r)
         { return l.first < r.first; });

    // shuffle the keys to randomise access order
    shuffle(begin(keys), end(keys), eng);

    // spawn a thread to time access to the unordered map
    auto unordered_future = async(launch::async, [&]()
                                  {
                                      auto start_time = chrono::system_clock::now();

                                      for (auto const& key : keys)
                                      {
                                          puser->sink(unordered.at(key));
                                      }
                                      
                                      auto stop_time = chrono::system_clock::now();
                                      auto diff =  stop_time - start_time;
                                      return diff; });

    // spawn a thread to time access to the ordered map
    auto ordered_future = async(launch::async, [&]
                                {
                                    
                                    auto start_time = chrono::system_clock::now();
                                    
                                    for (auto const& key : keys)
                                    {
                                        puser->sink(ordered.at(key));
                                    }
                                    
                                    auto stop_time = chrono::system_clock::now();
                                    auto diff =  stop_time - start_time;
                                    return diff; });

    // spawn a thread to time access to the flat map
    auto flat_future = async(launch::async, [&]
                             {
                                    
                                    auto start_time = chrono::system_clock::now();
                                    
                                    for (auto const& key : keys)
                                    {
                                        auto i = lower_bound(begin(flat_map),
                                                               end(flat_map),
                                                               key,
                                                               pair_less());
                                        if (i != end(flat_map) && i->first == key)
                                            puser->sink(i->second);
                                        else
                                            throw invalid_argument(key);
                                    }
                                    
                                    auto stop_time = chrono::system_clock::now();
                                    auto diff =  stop_time - start_time;
                                    return diff; });

    // synchronise all the threads and get the timings
    auto ordered_time = ordered_future.get();
    auto unordered_time = unordered_future.get();
    auto flat_time = flat_future.get();

    // print
    cout << "  ordered time: " << ordered_time.count() << endl;
    cout << "unordered time: " << unordered_time.count() << endl;
    cout << " flat map time: " << flat_time.count() << endl;

    return 0;
}