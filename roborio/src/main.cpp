#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Encoder.h>

#include "drivetrain/drivetrain.h"
#include "controller.h"
#include "util/cpreprocessor.h"

class Robot: public frc::SampleRobot {
public:
  FRC5572Controller driver;
  Encoder left, right;
  drivetrain::differential_drive drive;
  Robot() :
      driver(2), left(2, 3), right(0, 1, true), drive(
          drivetrain::differential_drive::fromMotors<frc::VictorSP>( {
              2, 3 }, { 0, 1 })) {
  }

  void RobotInit() {

  }

#define WHEEL_CONSTANT 109.7
#define DRIVETRAIN_WIDTH 27.8125
#define CURVE_P .5

  bool curve(double x, double y, double maxV, double minV) {
    drivetrain::differential_curve dc(x, y, DRIVETRAIN_WIDTH);
    double long_edge_dist  = fabs((dc.left() ? left : right).GetRaw()) / WHEEL_CONSTANT;
    double short_edge_dist = fabs((dc.left() ? right : left).GetRaw()) / WHEEL_CONSTANT;
    double error = (fabs(dc.length()) - long_edge_dist) / fabs(dc.length());
    if(error <= 0.0 || long_edge_dist > dc.length()) return true;
    error = math::smoothstep(error);
    
    double long_speed = error * (maxV - minV) + minV;
    double short_speed = dc() * long_speed;

    std::cout << long_speed << "," << short_speed << "(" << dc() << ") err: " << error << " goal: " << dc.length() << std::endl;
    double difference = (long_edge_dist * dc() - short_edge_dist) * CURVE_P; // How off is the short edge
    
    long_speed -= minV * difference;
    short_speed += minV * difference;

    drive.set(dc.left() ? long_speed : short_speed, dc.left() ? short_speed : long_speed);
    return false;
  }

  bool straight(double dist, double maxV){
    drive.set(maxV + maxV * .5 * (left.GetRaw() / WHEEL_CONSTANT - right.GetRaw() / WHEEL_CONSTANT),
        maxV + maxV * .5 * (right.GetRaw() / WHEEL_CONSTANT - left.GetRaw() / WHEEL_CONSTANT));
    return fabs(left.GetRaw() / WHEEL_CONSTANT) >= fabs(dist);
  }

  void Autonomous() {
    left.Reset();
    right.Reset();
    while (IsAutonomous() && IsEnabled() && !curve(-36, 36, .45, .4)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    drive.set(0, 0);
    left.Reset();
    right.Reset();
    Wait(0.5);
    /*
    while (IsAutonomous() && IsEnabled() && !straight(24, .45)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    //*/
    /*
    drive.set(0, 0);
    left.Reset();
    right.Reset();
    Wait(0.5);
    while (IsAutonomous() && IsEnabled() && !curve(36, 36, .45, .2)) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
    drive.set(0, 0);
    //*/
  }

  void OperatorControl() override {
    while (IsOperatorControl() && IsEnabled()) {
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
  }

  void Test() override {

  }
};

START_ROBOT_CLASS(Robot)
