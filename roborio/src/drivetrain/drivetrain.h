#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <vector>
#include <utility>

#include "../util/math.h"
#include "../util/varopt.h"

#if __EXCEPTIONS == 1 // NodeJS disables exceptions, so we can detect what is compiling this file

#else

#ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen shouldn't see the nowpi define, because it will document it otherwise
#define NOWPI // NodeJS doesn't have access to WPI Libraries
#endif

#endif

#ifndef NOWPI
#include "WPILib.h"

varopt_def(curve_p);
varopt_def(max_velocity);
varopt_def(min_velocity);

#endif

namespace drivetrain {
  /*! \brief Instructions for following an arc given a differential drive
   */
  class differential_curve {
  public:
    /*! \brief Constructor with point and drivetrain width
     */
    differential_curve(double x, double y, double w);
    /*! \brief Default destructor
     */
    inline ~differential_curve(){}
    /*! \brief Gets ratio of short edge to leading edge. Always between 0 and 1, and doubles for position ratio and velocity ratio.
     */
    inline double operator()(){return ratio;}
    /*! \brief Gets the side which is supposed to be the leading edge (true if left, false if right).
     */
    inline bool left(){return dl;};
    /*! \brief Gets overall length of leading edge. 
     */
    inline double length(){return ln;}
  private:
    double ratio;
    bool dl;
    double ln;
  };
  
  
  
#ifndef NOWPI
  class differential_drive {
  public:
    /*! \brief creates differential drive given a motor-type and ids
     */
    template <typename T>
    static differential_drive fromMotors(std::vector<unsigned> left, std::vector<unsigned> right);
    /*! \brief Default destructor
     */
    inline ~differential_drive(){}
    /*! Set motor speeds.
     */
    void set(double, double);
  private:
    inline differential_drive(std::vector<frc::SpeedController*> left, std::vector<frc::SpeedController*> right) : left(left), right(right) {}
    std::vector<SpeedController*> left, right;
  };
  #ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen shouldn't see the nowpi define, because it will document it otherwise
  namespace detail {
    bool driveto(drivetrain::differential_drive& drive, drivetrain::differential_curve& curve_geometry, double max_velocity, double min_velocity, double left_distance, double right_distance, double curve_proportional_gain);
  }
#endif
/*! \brief Update drivetrain to follow curve geometry
   *  \param drive drivetrain to control
   *  \param curve_geometry differential curve geometry for the drivetrain to follow
   *  \param left_distance current distance of the left encoder. Should be in same units as curve_geometry
   *  \param right_distance current distance of the right encoder. Should be in same units as curve_geometry
   * 
   * 
   * Optional Parameters
   * 
\f{tabular} {| c | c |}
\hline max\_velocity & maximum velocity to apply \\
\hline min\_velocity & minimum velocity to apply \\
\hline curve\_p & aggressiveness of corrections \\
\hline
\f}
   */
  template <typename ... VAROPT>
  inline bool driveto(drivetrain::differential_drive& drive, drivetrain::differential_curve& curve_geometry, double left_distance, double right_distance, VAROPT ... varopts){
    auto v = varopt<VAROPT...>(varopts...);
    varopt_eval(v, max_velocity, 1.0);
    varopt_eval(v, min_velocity, 0.3);
    varopt_eval(v, curve_p, 0.5);
    return detail::driveto(drive, curve_geometry, max_velocity, min_velocity, left_distance, right_distance, curve_p);
  }
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
