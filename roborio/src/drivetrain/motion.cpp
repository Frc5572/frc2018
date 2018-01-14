#include "drivetrain.h"
#include <tuple>

#include <cmath>
#include "../util/math.h"

double drivetrain::motion_profile::operator()(double t){
  
}

#define MOTION_TYPE std::vector<std::pair<double, std::vector<double> > >

// l1, l2, theta
std::tuple< double, double, double > curve_geometry(double x, double y, double w){
  if(y == 0) {
    if(x == 0) return std::make_tuple(0, 0, 0);
    double theta = x > 0 ? -PI : PI;
    double r = x > 0 ? x / 2.0 : -x / 2.0;
    double r1 = r - w / 2.0;
    double r2 = r + w / 2.0;
    double l1 = r1 * theta;
    double l2 = r2 * theta;
    if(x > 0) std::swap(l1, l2);
    return std::make_tuple(l1, l2, theta);
  }
  if(x == 0){
    return std::make_tuple(y, y, 0.0);
  }
  double theta = math::wrapping_limit(- 2.0 * atan2(x, y), - PI, PI);
  double r = (1.0 - cos(theta) / (x > 0 ? x : -x));
  double r1 = r - w / 2.0;
  double r2 = r + w / 2.0;
  double l1 = r1 * theta;
  double l2 = r2 * theta;
  if(x > 0) std::swap(l1, l2);
  return std::make_tuple(l1, l2, theta);
}

std::pair<drivetrain::motion_profile, drivetrain::motion_profile> drivetrain::diffprofile(std::vector<point> points, double w){
  
}