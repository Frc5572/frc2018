/*! \file auto.h Manages autonomous mode objectives
 */

#ifndef AUTO_H_
#define AUTO_H_

#include <WPILib.h>
#include "../drivetrain/drivetrain.h"

/*! \brief Paste mapper-generated code in here.
 */
void auto_run(frc::RobotBase *robot, drivetrain::differential_drive& drive, Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT, double CURVE_P, void (*intake_f)(double));

#endif
