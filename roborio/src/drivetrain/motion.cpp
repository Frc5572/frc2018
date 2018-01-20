#include "drivetrain.h"
#include <tuple>

#include <cmath>
#include "../util/math.h"

drivetrain::differential_curve::differential_curve(double x, double y, double w){
  left = true;
  ratio = 1;
  length = 0;
  if(y == 0){
    if(x == 0) return;
    double theta = x > 0 ? -PI : PI;
    double r = x > 0 ? x / 2.0 : -x / 2.0;
    double r1 = r - w / 2.0;
    double r2 = r + w / 2.0;
    double l1 = r1 * theta;
    double l2 = r2 * theta;
    if(x > 0) {left = false;}
    ratio = l2 / l1;
    length = l2;
  }
  if(x == 0){
    ratio = 1;

  }
  double theta = - 2.0 * atan2(x, y);
  double r = fabs(sin((PI - theta) / 2.0) * sqrt(x*x + y*y) / sin(theta));
  theta = math::wrapping_limit(theta, 0, 2.0 * PI);
  if(x > 0) theta -= 2.0 * PI;
  double r1 = r - w / 2.0;
  double r2 = r + w / 2.0;
  double l1 = r1 * theta;
  double l2 = r2 * theta;
  if(x > 0) left = false; // swap l1 and l2
  ratio = l2 / l1;
  length = l2;
}
