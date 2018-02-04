#ifndef FFST_MATH_H_
#define FFST_MATH_H_

#define PI 3.141592654

namespace math {

/*! \brief Enforces a wrapping limit on value.
 Wrapping is a constraint in which a minimum is equal to a maximum, and values exceeding either limit "wraps" to the other extremum.
 An example is angles. The angles 0, and \f$2\pi\f$ are equal, but if stored as a double, checking if they are equal will not produce the desired effect, so you may enforce a wrapping limit when checking for a value such as \f$\pi\f$.
 \param value value to limit
 \param min minimum value
 \param max maximum value
 */
inline double wrapping_limit(double value, double min, double max){
  while(value >= max) value -= (max - min);
  while(value < min) value += (max - min);
  return value;
}

/*! \brief Smooth interpolation function
 * Applys a smooth interpolation, such that at t=0 and t=1 the derivative of the interpolation equals 0. This is done using the function \f$3x^2-2x^3 | 0\leq x\leq 1 \f$.
 */
inline double smoothstep(double x){
  return x * x * (3 - 2 * x);
}

/*! \brief Smooth interpolation function
 * Applys a smooth interpolation, such that at t=0 and t=1 the 1st and 2nd derivative of the interpolation equals 0. This is done using the function \f$6x^5-15x^4+10x^3 | 0\leq x\leq 1 \f$.
 */
inline double smootherstep(double x){
  return x * x * x * (x * (x * 6 - 15) + 10);
}



}

#endif