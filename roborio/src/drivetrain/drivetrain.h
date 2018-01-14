#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <vector>
#include <utility>

#include "../util/math.h"

#if __EXCEPTIONS == 1 // NodeJS disables exceptions, so we can detect what is compiling this file

#else
#define NOWPI // NodeJS doesn't have access to WPI Libraries
#endif

#ifndef NOWPI

#include "WPILib.h"

#endif

namespace drivetrain {
  
  static double MAX_JERK = 0.3;
  
  struct point {
    double x, y;
  };
  
  class motion_profile {
  public:
    inline motion_profile(){}
    inline ~motion_profile(){}
    /*! \brief Retrieves velocity at a time 
     \param t time
     */
    double operator()(double t);
  private:
    friend std::pair<motion_profile, motion_profile> profile(std::vector<point>);
    std::vector<std::pair<double, std::vector<double> > > m_profile; // time, derivatives of distance (starting with velocity)
  };
  
  /*! \brief Generate differential drive motion profile. 
   * \param points coordinates of motion
   * \param w distance between left and right wheels   
   */
  std::pair<motion_profile, motion_profile> diffprofile(std::vector<point> points, double w);
#ifndef NOWPI
  class differential_drive {
  public:
    /*! \brief creates differential drive given a motor-type and ids
     */
    template <typename T>
    static differential_drive fromMotors(std::vector<unsigned> left, std::vector<unsigned> right);
    ~differential_drive();
  private:
    inline differential_drive(std::vector<frc::SpeedController*> left, std::vector<frc::SpeedController*> right) : left(left), right(right) {}
    std::vector<SpeedController*> left, right;
  };
#endif
};

// Impl
#ifndef NOWPI
/*! \brief creates differential drive given a motor-type and ids
 */
template <typename T>
inline drivetrain::differential_drive drivetrain::differential_drive::fromMotors(std::vector< unsigned > left, std::vector< unsigned > right){
  std::vector<frc::SpeedController*> l, r;
  for(unsigned i = 0; i < left.size(); i++){
    l.push_back(new T(left[i]));
  }
  for(unsigned i = 0; i < right.size(); i++){
    r.push_back(new T(right[i]));
  }
  return drivetrain::differential_drive(l, r);
}
#endif

#endif