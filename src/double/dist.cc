#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <limits>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include <cmath>

using namespace std;

#define D_R (M_PI / 180.0)
#define R_MAJOR 6378137.0
#define R_MINOR 6356752.3142
#define RATIO (R_MINOR / R_MAJOR)
#define ECCENT (sqrt(1.0 - (RATIO * RATIO)))
#define COM (0.5 * ECCENT)

// @brief The usual PI/180 constant
// const double DEG_TO_RAD = 0.017453292519943295769236907684886;
// @brief Earth's quatratic mean radius for WGS-84
const double EARTH_RADIUS_IN_METERS = 6372797.560856;

const double MERCATOR_MAX = 20037726.37;
// const double MERCATOR_MIN = -20037726.37;
const double EarthRadius = 6378137;
static inline double deg_rad(double ang) { return ang * D_R; }
static inline double rad_deg(double ang) { return ang / D_R; }

// https://tech.meituan.com/2014/09/05/lucene-distance.html

// Haversine
double dist_ha(double lon1, double lat1, double lon2, double lat2)
{
    double lon = deg_rad(lon2 - lon1);
    double lat = deg_rad(lat2 - lat1);
    double a = (sin(lat / 2) * sin(lat / 2)) + cos(deg_rad(lat1)) *
                                                   cos(deg_rad(lat2)) *
                                                   (sin(lon / 2) * sin(lon / 2));
    double angle = 2 * atan2(sqrt(a), sqrt(1 - a));

    return angle * EARTH_RADIUS_IN_METERS;
}

static double dist_redis(double lon1d, double lat1d, double lon2d, double lat2d)
{
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg_rad(lat1d);
    lon1r = deg_rad(lon1d);
    lat2r = deg_rad(lat2d);
    lon2r = deg_rad(lon2d);
    u = sin((lat2r - lat1r) / 2);
    v = sin((lon2r - lon1r) / 2);
    return 2.0 * EARTH_RADIUS_IN_METERS *
           asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

static constexpr double s_r_max = 6378137.0;      //赤道半径
static constexpr double s_r_min = 6356725.0;      //极地半径
static constexpr double s_deg2rad = M_PI / 180.0; //角度到弧度的常数

static double dist_doca(double lng1, double lat1, double lng2, double lat2)
{
    double r_lat_1 = deg_rad(lat1);
    double r_lng_1 = deg_rad(lng1);
    double r_lat_2 = deg_rad(lat2);
    double r_lng_2 = deg_rad(lng2);
    double abs_lat1 = fabs(lat1);

    double Ec = s_r_min + (s_r_max - s_r_min) * (90.0 - abs_lat1) / 90.0;
    double Ed = Ec * cos(r_lat_1);
    double dx = (r_lng_2 - r_lng_1) * Ed;
    double dy = (r_lat_2 - r_lat_1) * Ec;
    return sqrt(dx * dx + dy * dy);
}

std::string toString(double o)
{
    std::ostringstream os;
    os << std::setprecision(std::numeric_limits<double>::max_digits10) << o;
    return os.str();
}

double naive(const char *p)
{
    double r = 0.0;
    bool neg = false;
    if (*p == '-')
    {
        neg = true;
        ++p;
    }
    while (*p >= '0' && *p <= '9')
    {
        r = (r * 10.0) + (*p - '0');
        ++p;
    }
    if (*p == '.')
    {
        double f = 0.0;
        int n = 0;
        ++p;
        while (*p >= '0' && *p <= '9')
        {
            f = (f * 10.0) + (*p - '0');
            ++p;
            ++n;
        }
        r += f / std::pow(10.0, n);
    }
    if (neg)
    {
        r = -r;
    }
    return r;
}

// us
uint64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + tv.tv_usec;
}

// clock() 函数仅统计 cpu 时间，不算 sleep

void case1()
{
    double lng1 = 116.30666213;
    double lat1 = 40.03825211;

    double lng2 = 116.30666213;
    double lat2 = 40.03815211;

    double dist1 = dist_redis(lng1, lat1, lng2, lat2);
    double dist2 = dist_doca(lng1, lat1, lng2, lat2);
    double dist3 = dist_ha(lng1, lat1, lng2, lat2);

    double dist4 = dist_doca(110.888579405, 34.516926809, 110.888351899, 34.517041499);

    std::cout << "dist1=" << dist1 << std::endl;
    std::cout << "dist2=" << dist2 << std::endl;
    std::cout << "dist3=" << dist3 << std::endl;

    std::cout << "dist4=" << dist4 << std::endl;

    std::cout << "dist4(toString)=" << toString(dist4) << std::endl;
}

std::vector<std::string> SplitStringDelim(const std::string &arg,
                                          const std::string &delim)
{
    std::vector<std::string> splits;
    // splits.reserve(4);

    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.push_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.push_back(arg.substr(beg));

    return splits;
}
std::vector<std::string> SplitStringDelim2(const std::string &arg,
                                           const std::string &delim)
{
    std::vector<std::string> splits;
    splits.reserve(4);

    std::size_t beg = 0;
    std::size_t delim_size = delim.size();
    std::size_t pos = arg.find(delim);
    while (pos != arg.npos)
    {
        splits.push_back(arg.substr(beg, pos - beg));
        beg = pos + delim_size;
        pos = arg.find(delim, beg);
    }
    splits.push_back(arg.substr(beg));

    return splits;
}

class GeoPosition
{
public:
    std::string latitude;
    std::string longitude;

    double lat;
    double lng;

    explicit GeoPosition(const std::string &la = "", const std::string &lo = "")
        : latitude(la), longitude(lo)
    {
        lat = atof(la.c_str());
        lng = atof(lo.c_str());
    }
    void setPos(const std::string &la = "", const std::string &lo = "")
    {
        latitude = la;
        longitude = lo;
        lat = atof(la.c_str());
        lng = atof(lo.c_str());
    }

    std::string ToString() const { return longitude + "," + latitude; }
};

void getBizValueCheckEmpty(const string &dest, string &output)
{
    output = dest.substr(0, dest.length() - 1);
    if (output.length() > 0)
    {
        if (output == "test")
        {
            output.clear();
            output = "";
        }
    }
}

class GeoObject
{
public:
    GeoPosition position;
    std::string uid;
    std::string value;
    double dist;

    GeoObject() {}

    GeoObject(const GeoPosition &pos, const std::string &i,
              const std::string &val, double di = 0)
        : position(pos), uid(i), value(val), dist(di) {}
};

struct GeoObject3
{
    std::string latitude;
    std::string longitude;
};
struct GeoObject2
{
    // public:
    std::string latitude;
    std::string longitude;
    // double lat;
    // double lng;

    std::string uid;
    std::string value;
    double dist;

    // // GeoObject2() {}

    // GeoObject2();
    // GeoObject2(const GeoObject2 &) = default;
    // GeoObject2 &operator=(const GeoObject2 &other);

    // // GeoObject2(GeoObject2 const &) = delete;
    // // GeoObject2 &operator=(GeoObject2 const &) = delete;

    GeoObject2(const GeoObject2 &other) : latitude(std::move(other.latitude)), longitude(std::move(other.longitude)), uid(std::move(other.uid)), value(std::move(other.value)), dist(other.dist)
    {
        // printf("copy constructed\n");
    }

    explicit GeoObject2(const std::string &la, const std::string &lo, const std::string &i,
                        const std::string &val, double di = 0)
        : latitude(la), longitude(lo), uid(i), value(val), dist(di)
    {
        // printf("constructed\n");
    }

    explicit GeoObject2(const std::string &&la, const std::string &&lo, const std::string &&i,
                        const std::string &&val, double di = 0)
        : latitude(std::move(la)), longitude(std::move(lo)), uid(std::move(i)), value(std::move(val)), dist(di)
    {
        // printf("move\n");
    }
    // ~GeoObject2() {
    //     //  printf("clean\n");
    // }
};

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

std::vector<std::string> prepareKey(int N = 1000)
{

    std::vector<std::string> result;
    for (size_t i = 0; i < N; i++)
    {
        std::string arg = "663$^$1220101200033110113023200213132&&1062943904942260224&&";

        // 27.090602&&114.977901

        arg.append(toString(fRand(27, 28)));
        arg.append("&&");
        arg.append(toString(fRand(114, 115)));
        // std::cout << arg << std::endl;
        result.push_back(arg);
    }

    return result;
}

std::map<int, std::pair<double, double>> prepareKeyDouble(int N = 1000)
{
    std::map<int, std::pair<double, double>> result;
    for (size_t i = 0; i < N; i++)
    {
        auto lat = fRand(27, 28);
        auto lng = fRand(114, 115);

        result.insert({(int)i, {lat, lng}});
    }

    return result;
}

std::vector<std::string> prepareLat(int N = 1000)
{

    std::vector<std::string> result;
    for (size_t i = 0; i < N; i++)
    {
        result.push_back(toString(fRand(27, 28)));
    }

    return result;
}

void caseAtof(int N = 1000)
{

    std::string la = "27.090602";
    std::string ln = "114.090602";

    std::vector<std::string> splits = prepareLat(N * 2);

    auto start = now();

    for (const auto &arg : splits)
    {
        auto lat = atof(arg.c_str());
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "caseAtof N=" << N << " dt: " << dt << "us"
              << " splits.size=" << splits.size() << std::endl;
}

int caseGetBizValueCheckEmpty(int N = 1000)
{
    auto start = now();
    std::string k = "663$^$1220101200033110113023200213132&&1062943904942260224&&";

    for (size_t i = 0; i < N; i++)
    {
        std::string val;
        getBizValueCheckEmpty(k, val);
    }

    auto end = now();
    auto dt = end - start;

    std::cout << "caseGetBizValueCheckEmpty N=" << N << " dt: " << dt << "us" << std::endl;
}

void caseDistDoca(int N = 1000)
{
    auto keys = prepareKeyDouble(N);
    GeoPosition pos("27.390602", "114.1779");

    auto start = now();

    for (const auto &k : keys)
    {
        dist_doca(pos.lng, pos.lat, k.second.second, k.second.first);
    }

    auto end = now();
    auto dt = end - start;

    std::cout << "caseDistDoca N=" << N << " dt: " << dt << "us" << std::endl;
}

int clacDist(int N = 1000)
{

    auto keys = prepareKey(N);

    std::vector<std::string> preParts;
    preParts.push_back("663$^$1220101200033110113023200213132");
    preParts.push_back("1062943904942260224");
    preParts.push_back(toString(fRand(27, 28)));
    preParts.push_back(toString(fRand(27, 28)));
    GeoPosition pos("27.390602", "114.1779");

    auto start = now();

    double radius = 100000.0;

    std::vector<GeoObject> values;

    for (const auto &k : keys)
    {
        // auto parts = preParts; // SplitStringDelim(k, "&&");
        auto parts = SplitStringDelim(k, "&&");

        GeoPosition obj_pos(parts[2], parts[3]);

        double dist = dist_doca(pos.lng, pos.lat, obj_pos.lng, obj_pos.lat);
        if (dist > radius)
        {
            continue;
        }
        std::string val;
        getBizValueCheckEmpty(k, val);

        GeoObject obj(obj_pos, parts[1], val, dist);
        values.push_back(std::move(obj));
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "clacDist N=" << N << " dt: " << dt << "us"
              << " values.size=" << values.size() << std::endl;
}

int clacDist2(int N = 1000)
{

    auto keys = prepareKey(N);

    std::vector<std::string> preParts;
    preParts.push_back("663$^$1220101200033110113023200213132");
    preParts.push_back("1062943904942260224");
    preParts.push_back(toString(fRand(27, 28)));
    preParts.push_back(toString(fRand(27, 28)));

    GeoPosition pos("27.390602", "114.1779");

    auto start = now();
    double radius = 100000.0;

    std::vector<GeoObject2> values;
    values.reserve(1000);

    for (const auto &k : keys)
    {
        // auto parts = preParts; // SplitStringDelim(k, "&&");
        auto parts = SplitStringDelim2(k, "&&"); // 6-7ms

        // GeoPosition obj_pos(parts[2], parts[3]);
        double lat = naive(parts[2].c_str());
        double lng = naive(parts[3].c_str()); // us level

        // double lat = 27.090602;
        // double lng = 114.090602;

        double dist = dist_doca(pos.lng, pos.lat, lng, lat); // 1-2ms
        if (dist > radius)
        {
            continue;
        }
        // std::string val;
        // getBizValueCheckEmpty(k, val);

        //  GeoObject2(const std::string &la, const std::string &lo,  double lat,double lng,  const std::string &i,
        //   const std::string &val, double di = 0)

        // GeoObject2 obj(std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist);
        // values.push_back(std::move(obj));

        //  const std::string latitude;
        // const std::string longitude;

        // const std::string uid;
        // const std::string value;
        // double dist;
        // values.emplace_back(GeoObject2{std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist});
        // GeoObject2 ob{parts[2], parts[3], parts[1], k, dist};

        GeoObject3 ok{"person", "name"};

        // values.emplace_back(std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist);

        // values.emplace_back(std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist);
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "clacDist2 N=" << N << " dt: " << dt << "us"
              << " values.size=" << values.size() << std::endl;
}

// worse case
int clacDist3(int N = 1000)
{

    auto keys = prepareKey(N);

    std::vector<std::string> preParts;
    preParts.push_back("663$^$1220101200033110113023200213132");
    preParts.push_back("1062943904942260224");
    preParts.push_back(toString(fRand(27, 28)));
    preParts.push_back(toString(fRand(27, 28)));

    GeoPosition posObj("27.390602", "114.1779");
    std::string delim = "&&";
    std::size_t delim_size = delim.size();

    auto start = now();
    double radius = 100000.0;

    std::vector<GeoObject2> values;
    values.reserve(1000);

    for (const auto &k : keys)
    {
        // auto parts = preParts; // SplitStringDelim(k, "&&");
        // auto parts = SplitStringDelim2(k, "&&"); // 6-7ms

        /********************** std::vector<std::string> splits;
         * const std::string &arg,
                                               const std::string &delim)
    {
        splits.reserve(4);

        std::size_t beg = 0;
        std::size_t delim_size = delim.size();
        std::size_t pos = arg.find(delim);
        while (pos != arg.npos)
        {
            splits.push_back(arg.substr(beg, pos - beg));
            beg = pos + delim_size;
            pos = arg.find(delim, beg);
        }
        splits.push_back(arg.substr(beg));
        */
        std::string kt = k;
        std::size_t beg = 0;
        std::size_t pos = k.find(delim);
        std::string k0 = k.substr(beg, pos - beg);

        beg = pos + delim_size;
        pos = k.find(delim, beg);
        std::string k1 = k.substr(beg, pos - beg);

        beg = pos + delim_size;
        pos = k.find(delim, beg);
        std::string k2 = k.substr(beg, pos - beg);

        beg = pos + delim_size;
        pos = k.find(delim, beg);
        std::string k3 = k.substr(beg, pos - beg);

        //    std::cout << "k==" << k << std::endl;
        //    std::cout << "k0==" << k0 << std::endl;
        //    std::cout << "k1==" << k1 << std::endl;
        //    std::cout << "k2==" << k2 << std::endl;
        //    std::cout << "k3==" << k3 << std::endl;

        // GeoPosition obj_pos(parts[2], parts[3]);
        double lat = atof(k2.c_str());
        double lng = atof(k3.c_str()); // us level

        // double lat = 27.090602;
        // double lng = 114.090602;

        double dist = dist_doca(posObj.lng, posObj.lat, lng, lat); // 1-2ms
        if (dist > radius)
        {
            continue;
        }
        // std::string val;
        // getBizValueCheckEmpty(k, val);

        //  GeoObject2(const std::string &la, const std::string &lo,  double lat,double lng,  const std::string &i,
        //   const std::string &val, double di = 0)

        // GeoObject2 obj(std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist);
        // values.push_back(std::move(obj));

        //  const std::string latitude;
        // const std::string longitude;

        // const std::string uid;
        // const std::string value;
        // double dist;
        // values.emplace_back(GeoObject2{std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist});
        // GeoObject2{parts[2], parts[3], parts[1], k, dist};
        // values.emplace_back(std::move(parts[2]), std::move(parts[3]), std::move(parts[1]), std::move(k), dist);
    }

    auto end = now();

    auto dt = end - start;

    std::cout << "clacDist3 N=" << N << " dt: " << dt << "us"
              << " values.size=" << values.size() << std::endl;
}

int main()
{

    auto d = dist_doca(116.307254, 40.038921, 116.307831, 40.03903);

    std::cout << d << std::endl;

    // case1();
    int N = 32000;

    caseAtof(N);
    // caseGetBizValueCheckEmpty(N);

    clacDist();
    caseDistDoca(N);

    clacDist(N);
    clacDist2();
    clacDist2(N);

    // clacDist3(N);
}