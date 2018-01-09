#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <cmath>

#include <iostream>

#define HALF_PI 1.570796327

struct Point {
  double x, y;
  double heading;
};

inline Point operator+(Point a, Point b){
  return {a.x + cos(a.heading) * b.x + sin(a.heading) * b.y, a.y - sin(a.heading) * b.x + cos(a.heading) * b.y, a.heading + b.heading};
}

inline Point curveamount(double L1, double L2, double W){ // Turn two encoder readings (in coordinate units) into coordinates. Doesn't work yet 100% of the time (try 0, Wpi, then Wpi, 0. Answer should be 2W), but turns less than 90 degrees usually work (tested with W/2pi).
  if(fabs(L1 - L2) < 1e-6){ // If close enough to straight (evals to inf otherwise)
    return {0, L1, 0};
  }
  double r2 = (L2*W)/(L1-L2); // Radius of L2 
  double r = r2+(W/2); // Center of robot
  double radians;
  if(L1 > L2){ // choose the radians with better precision. Originally to avoid divide by zero errors, but broke whenever you input 0 and pi/2*W. This works in that case.
    radians = L1 / (r2 + W); // arc length over radius
  }
  else{ 
    radians = L2 / r2; // arc length over radius
  }
  
  return {r + r * cos(radians), // Center of the concentric circle equals -r
	  r * sin(radians),
	  radians};
}

#endif