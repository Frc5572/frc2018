#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Encoder.h>

#include "drivetrain/drivetrain.h"
#include "input/controller.h"
#include "util/cpreprocessor.h"

class Robot: public frc::SampleRobot {
public:
  FRC5572Controller driver;
  Encoder left, right;
  drivetrain::differential_drive drive;
  Robot() :
      driver(2), left(2, 3), right(0, 1, true), drive(
          drivetrain::differential_drive::fromMotors<frc::VictorSP>( {
              0, 1 }, { 2, 3 })) {
  }

  void RobotInit() {

  }

#define WHEEL_CONSTANT 204
#define DRIVETRAIN_WIDTH 20.375
#define CURVE_P .5

  void Autonomous() {
    drivetrain::differential_curve dc(-36, 36, DRIVETRAIN_WIDTH);
    drivetrain::differential_curve dc1(0, 36, DRIVETRAIN_WIDTH);
    drivetrain::differential_curve dc2(24, 24, DRIVETRAIN_WIDTH);
    SmartDashboard::PutNumber("Auto_Seq", 0);
    left.Reset();
    right.Reset();
    while (IsAutonomous() && IsEnabled()
        && !drivetrain::driveto(drive, dc,
            fabs(left.GetRaw() / WHEEL_CONSTANT),
            fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P, max_velocity = 0.45)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    SmartDashboard::PutNumber("Auto_Seq", 1);
    drive.set(0, 0);
    left.Reset();
    right.Reset();
    Wait(0.5);
    while (IsAutonomous() && IsEnabled()
        && !drivetrain::driveto(drive, dc1, fabs(left.GetRaw() / WHEEL_CONSTANT),
            fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P, max_velocity = 0.45)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    SmartDashboard::PutNumber("Auto_Seq", 2);
    drive.set(0, 0);
    Wait(0.5);
    left.Reset();
    right.Reset();
    SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
    SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    while (IsAutonomous() && IsEnabled()
        && !drivetrain::driveto(drive, dc2,
            fabs(left.GetRaw() / WHEEL_CONSTANT),
            fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P, max_velocity = -0.45, min_velocity = -0.3)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    drive.set(0, 0);
    SmartDashboard::PutNumber("Auto_Seq", 3);
    /*
     while (IsAutonomous() && IsEnabled() && !driveto(0, 24, .45, .4)) {
     SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
     SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
     }
     //*/
    /*
     drive.set(0, 0);
     left.Reset();
     right.Reset();
     Wait(0.5);
     while (IsAutonomous() && IsEnabled() && !driveto(36, 36, .45, .2)) {
     SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
     SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
     }
     drive.set(0, 0);
     //*/
  }

  void OperatorControl() override {
    while (IsOperatorControl() && IsEnabled()) {
      SmartDashboard::PutNumber("left", left.GetRaw());
      SmartDashboard::PutNumber("right", right.GetRaw());
    }
  }

  void Test() override {

  }
};

START_ROBOT_CLASS(Robot)
