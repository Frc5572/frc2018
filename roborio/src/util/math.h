#ifndef FFST_MATH_H_
#define FFST_MATH_H_

#define PI 3.141592654

namespace math {

/*! \brief Enforces a wrapping limit on value.
 Wrapping is a constraint in which a minimum is equal to a maximum, and values exceeding either limit "wraps" to the other extremum.
 An example is angles. The angles 0, and \f$2\pi\f$ are equal in angles, so you may enforce a wrapping limit when checking for a value such as \f$\pi\f$.
 \param value value to limit
 \param min minimum value
 \param max maximum value
 */
inline double wrapping_limit(double value, double min, double max){
  while(value > max) value -= (max - min);
  while(value < min) value += (max - min);
  return value;
}

}

#endif