#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <cmath>

#include <iostream>

#define HALF_PI 1.570796327

/*! \struct Curve
 *  \brief Describes the position and direction of a robot after a curve amount.
 */
struct Curve {
  double x; //!< Horizontal Position
  double y; //!< Vertical Position
  double heading; //!< Direction of the robot in radians
};

/*! \struct DoublePair
 *  \brief Stores generic 2-value real number objects. Examples of usage are 2d coordinates and differential drive outputs.
 */
struct DoublePair {
  double u; //!< First Value
  double v; //!< Second Value
};

/*! \brief Adds two curves
 */
inline Curve operator+(Curve a, Curve b){
  double bx = cos(a.heading) * b.x - sin(a.heading) * b.y;
  double by = sin(a.heading) * b.x + cos(a.heading) * b.y;
  return {a.x + bx, a.y + by, a.heading + b.heading};
}

/*! \brief Turn two encoder readings (in coordinate units) into coordinates.
 * @image latex driving_image.png
 * \latexonly

\begin{equation}
r=\frac{y}{sin(\theta)}
\end{equation}

\begin{equation}
x=\frac{y}{sin(\theta)} 
\end{equation}

\endlatexonly
 */
inline Curve curveamount(double L1, double L2, double W){ // Doesn't work yet 100% of the time (try 0, Wpi, then Wpi, 0. Answer should be 2W), but turns less than 90 degrees usually work (tested with W/2pi).
  if(fabs(L1 - L2) < 1e-6){ // If close enough to straight (evals to inf otherwise)
    return {0, L1, 0};
  }
  double r, radians, x, y;
  bool l2gtl1;
  if(L2 > L1){
    r = (L1*W)/(L2-L1)+(W/2);
    radians = L2/(W+(L1*W)/(L2-L1));
    l2gtl1 = true;
    x = -r + r * cos(radians);
    y = r * sin(radians);
  } else {
    r = (L2*W)/(L1-L2)+(W/2);
    radians = L1/(W+(L2*W)/(L1-L2));
    l2gtl1 = false;
    x = r - r * cos(radians);
    y = r * sin(radians);
    radians = -radians;
  }
  return {x, y, radians};
}



#endif