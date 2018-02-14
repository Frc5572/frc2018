#include "../drivetrain/drivetrain.h"
#include <tuple>

#include <cmath>
#include "../util/math.h"
#include <iostream>

unsigned test = 0;


bool drivetrain::detail::driveto(drivetrain::differential_drive& drive, drivetrain::differential_curve& dc, double maxV, double minV, double ldist, double rdist, double curve_p) {
	if(dc() == 1){
		drive.set(maxV, maxV);
		if(ldist >= dc.length()) return true;
		return false;
	}
	double long_edge_dist  = fabs(dc.left() ? ldist : rdist);
    double short_edge_dist = fabs(dc.left() ? rdist : ldist);
    double error = (fabs(dc.length()) - long_edge_dist) / fabs(dc.length());
#ifndef NOWPI
    SmartDashboard::PutNumber("long_edge", long_edge_dist);
    SmartDashboard::PutNumber("prerror", error);
    SmartDashboard::PutNumber("dc.length", dc.length());
#endif
    if(error <= 0.0 || long_edge_dist > fabs(dc.length())) return true;
#ifndef NOWPI
    SmartDashboard::PutNumber("error", error);
    SmartDashboard::PutNumber("Difference Check", test++);
#endif
    error = math::smootherstep(error);
    
    double long_speed = error * (maxV - minV) + minV;
    double short_speed = dc() * long_speed;

    double difference = ((long_edge_dist * dc()) - short_edge_dist) * curve_p; // How off is the short edge
    
    long_speed -= minV * difference;
    short_speed += minV * difference;

    drive.set(dc.left() ? long_speed : short_speed, dc.left() ? short_speed : long_speed);
    return false;
  }

drivetrain::differential_curve::differential_curve(double x, double y, double w){
  dl = false;
  ratio = 1;
  ln = 0;
  if(y == 0){
    if(x == 0) return;
    double theta = x > 0 ? -PI : PI;
    double r = x > 0 ? x / 2.0 : -x / 2.0;
    double r1 = r - w / 2.0;
    double r2 = r + w / 2.0;
    double l1 = r1 * theta;
    double l2 = r2 * theta;
    if(x > 0) {dl = true;}
    ratio = l2 / l1;
    if(ratio > 1.0) ratio = 1.0 / ratio;
    ln = l2;
  }
  if(x == 0){
    ratio = 1;
    ln = y;
    dl = false;
    return;
  }
  double theta = - 2.0 * atan2(x, y);
  double r = fabs(sin((PI - theta) / 2.0) * sqrt(x*x + y*y) / sin(theta));
  std::cout << r << std::endl;
  theta = math::wrapping_limit(theta, 0, 2.0 * PI);
  SmartDashboard::PutNumber("Radius", r);
  SmartDashboard::PutNumber("Theta", theta);
  if(x > 0) theta -= 2.0 * PI;
  double r1 = r - w / 2.0;
  double r2 = r + w / 2.0;
  double l1 = r1 * theta;
  double l2 = r2 * theta;
  if(x > 0) dl = true; // swap l1 and l2
  ratio = l2 / l1;
  if(ratio > 1.0) ratio = 1.0 / ratio;
  SmartDashboard::PutNumber("Ratio", ratio);
  ln = l2;
  SmartDashboard::PutNumber("Goal", ln);
}
