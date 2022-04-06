#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include <cassert>

struct GeoObjCache
{
    const std::string latitude;
    const std::string longitude;
    const std::string uid;
    double lat;
    double lng;
};

struct GeoObjMapCacheStripe
{
    std::mutex mutex_;
    std::unordered_map<std::string, GeoObjCache> keyObjs;
};

uint32_t murmur_hash2(unsigned char *data, size_t len)
{
    uint32_t h, k;

    h = 0 ^ len;

    while (len >= 4)
    {
        k = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= 0x5bd1e995;
        k ^= k >> 24;
        k *= 0x5bd1e995;

        h *= 0x5bd1e995;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
    case 3:
        h ^= data[2] << 16;
        /* fall through */
    case 2:
        h ^= data[1] << 8;
        /* fall through */
    case 1:
        h ^= data[0];
        h *= 0x5bd1e995;
    }

    h ^= h >> 13;
    h *= 0x5bd1e995;
    h ^= h >> 15;

    return h;
}

struct murmur_hash
{
    size_t operator()(const std::string &key) const
    {
        return murmur_hash2((unsigned char *)key.data(), key.size());
    }
};

struct GeoObjMapCache
{
    explicit GeoObjMapCache(size_t num_stripes) : num_stripes_(num_stripes)
    {
        map_stripes_.reserve(num_stripes);
        for (size_t i = 0; i < num_stripes; i++)
        {
            GeoObjMapCacheStripe *stripe = new GeoObjMapCacheStripe();
            map_stripes_.push_back(stripe);
        }
    }

    ~GeoObjMapCache()
    {
        for (auto stripe : map_stripes_)
        {
            delete stripe;
        }
    }

    size_t GetStripe(const std::string &key) const
    {
        assert(num_stripes_ > 0);
        static murmur_hash hash;
        size_t stripe = hash(key) % num_stripes_;
        return stripe;
    }

    std::vector<GeoObjMapCacheStripe *> map_stripes_;

    const size_t num_stripes_;
};

std::shared_ptr<GeoObjMapCache> geoObjMapCache =
    std::make_shared<GeoObjMapCache>(1024);

void read(int i, int num)
{
    std::string pk = std::to_string(i) + std::to_string(num);
    size_t stripe_num = geoObjMapCache->GetStripe(pk);
    GeoObjMapCacheStripe *stripe = geoObjMapCache->map_stripes_.at(stripe_num);
    stripe->keyObjs.find(pk);
}

void write(int i, int num)
{
    std::string pk = std::to_string(i) + std::to_string(num);
    size_t stripe_num = geoObjMapCache->GetStripe(pk);
    GeoObjMapCacheStripe *stripe = geoObjMapCache->map_stripes_.at(stripe_num);
    {
        stripe->mutex_.lock();
        stripe->keyObjs.insert({pk, {"parts[2]", "parts[3]", "parts[1]", 22.11, 109.11}});
        stripe->mutex_.unlock();
    }
}

void readAndWrite(int i, int num = 2000)
{
    for (int j = 0; j < num; j++)
    {
        std::string pk = std::to_string(i) + "_" + std::to_string(j);
        // std::cout << pk << std::endl;
        size_t stripe_num = geoObjMapCache->GetStripe(pk);
        GeoObjMapCacheStripe *stripe = geoObjMapCache->map_stripes_.at(stripe_num);
        stripe->mutex_.lock();
        auto rtn = stripe->keyObjs.find(pk);
        stripe->mutex_.unlock();

        if (rtn == stripe->keyObjs.end())
        {
            {
                stripe->mutex_.lock();
                stripe->keyObjs.insert({pk, {"parts[2]", "parts[3]", "parts[1]", 22.11, 109.11}});
                stripe->mutex_.unlock();
            }
        }
    }
}

void readM(int i, int N = 2000)
{
    for (int j = 0; j < N; j++)
    {
        read(i, j);
    }
}

void writeM(int i, int N = 2000)
{
    for (int j = 0; j < N; j++)
    {
        write(i, j);
    }
}

void case1()
{
    std::cout << "case1: " << std::endl;

    std::vector<std::thread> ver;
    int num = 10000;
    for (auto i = 0; i < 20; ++i)
    {
        ver.emplace_back(writeM, i, num);
        ver.emplace_back(readM, i, num);
    }

    for (auto &t : ver)
    {
        t.join();
    }
    std::cout << num << std::endl;
}

void case2()
{
    std::cout << "case2: " << std::endl;
    std::vector<std::thread> ver;
    int num = 10000;
    for (auto i = 0; i < 20; ++i)
    {
        ver.emplace_back(readAndWrite, i, num);
    }

    for (auto &t : ver)
    {
        t.join();
    }
    std::cout << num << std::endl;
}

int main()
{
    case2();
}
