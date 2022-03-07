#include <iostream>
#include <string>
#include <math.h>
#include <iomanip>
#include <limits>
#include <sstream>

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

int main()
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