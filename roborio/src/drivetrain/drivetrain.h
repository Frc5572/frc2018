#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include <vector>
#include <utility>

#include "../util/math.h"

#if __EXCEPTIONS == 1 // NodeJS disables exceptions, so we can detect what is compiling this file

#else

#ifndef DOXYGEN_SHOULD_SKIP_THIS // Doxygen shouldn't see the nowpi define, because it will document it otherwise
#define NOWPI // NodeJS doesn't have access to WPI Libraries
#endif

#endif

#ifndef NOWPI
#include "WPILib.h"
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
    inline double& operator()(){return ratio;}
    /*! \brief Gets the side which is supposed to be the leading edge (true if left, false if right).
     */
    inline bool& left(){return dl;};
    /*! \brief Gets overall length of leading edge. 
     */
    inline double& length(){return ln;}
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
