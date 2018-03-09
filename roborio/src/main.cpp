#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Encoder.h>
#include <CameraServer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

#include "drivetrain/drivetrain.h"
#include "input/controller.h"
#include "util/cpreprocessor.h"
#include "autonomous/auto.h"

void cameraThread() {
  cs::UsbCamera camera = cs::UsbCamera("default_cam", 0);
  cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo(
      "DriveStationVideo", 640, 480);
  cs::CvSink front = frc::CameraServer::GetInstance()->GetVideo(camera);
  cv::Mat mat;
  while (1) {
    front.GrabFrame(mat);
    outputStream.PutFrame(mat);
  }
}

VictorSP intake_left { 5 }, intake_right { 4 }, intake_lift { 3 },
    climber { 2 };
bool can_down = false;
DigitalInput top { 5 }, bottom { 4 }, ctop { 6 };

class Robot: public frc::SampleRobot {
public:
  FRC5572Controller driver, op;
  Encoder left, right;
  drivetrain::differential_drive drive;
  Robot() :
      driver(2), op(0), left(0, 1), right(2, 3), drive(
          drivetrain::differential_drive::fromMotors<frc::VictorSP>( {
              6, 7 }, { 8, 9 })) {
  }

  void RobotInit() {
    std::thread t(cameraThread);
    t.detach();
    auto_setup();
  }


#define WHEEL_CONSTANT 155.15686 // at 51", encoders read (8105, 7961, 7909, 7828, 8079, 7847, 7874, 7701)
#define DRIVETRAIN_WIDTH 20.5
//#define DRIVETRAIN_WIDTH 17.0
#define CURVE_P .5
#define SLIPPING_MULTIPLIER .8

  static void intake(double d) {
    intake_left.Set(d);
    intake_right.Set(-d);
    Wait(2.0);
    intake_left.Set(0);
    intake_right.Set(0);
  }

  static bool lift(double ia) {
    double intake_amount = ia;
    SmartDashboard::PutBoolean("top", top.Get());
    SmartDashboard::PutBoolean("bottom", !bottom.Get());
    SmartDashboard::PutNumber("ia", ia);
    if (intake_amount > 0 && top.Get()) {
      intake_amount = 0;
    }
    intake_amount += 0.06; // TODO: Change back to 0.06
    if (intake_amount < 0 && !bottom.Get()) {
      intake_amount = 0;
    }
    intake_lift.Set(intake_amount);
    return top.Get() && bottom.Get(); // || !bottom.Get();
  }

  static bool climb(double c, bool t) {
    double intake_amount = c;
    SmartDashboard::PutBoolean("ctop", !ctop.Get());
    SmartDashboard::PutNumber("climb", c);
    if (intake_amount < 0 && !ctop.Get()) {
      intake_amount = 0;
      can_down = true;
    }
    if(t)
    if (intake_amount > 0 && !can_down) {
      intake_amount = 0;
    }
    climber.Set(intake_amount);
    return !ctop.Get(); // || !bottom.Get();
  }

  void Autonomous() override {
    auto_run(this, drive, left, right, DRIVETRAIN_WIDTH, WHEEL_CONSTANT, CURVE_P, intake, lift);
  }

  void OperatorControl() override {
    can_down = false;
    while (IsOperatorControl() && IsEnabled()) {
      double mul = .4 + .25 * (1.0 - driver.LT()) + .25 * driver.RT();
      drive.set(mul * driver.L().second, mul * driver.R().second);
      intake_left.Set(.5 * (op.LT() - op.RT()));
      intake_right.Set(-.5 * (op.LT() - op.RT()));
      double intake_amount = -op.R().second;
      lift(intake_amount > 0 ? .6 * intake_amount : .6 * intake_amount);
      climb(.8 * op.L().second, true);
      SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
      SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
    }
  }

  void Test() override {
	SmartDashboard::PutString("debug_procedure", "Starting Debug Procedure");
    left.Reset();
    right.Reset();
    SmartDashboard::PutString("debug_procedure", "Move Forward 50 inches. Then Press A.");
    while(IsTest() && IsEnabled() && !op.A());
    double error = (left.Get() - right.Get()) / (left.Get() + right.Get()), value = (left.Get() + right.Get()) / 2;
    std::stringstream ss1, ss2;
    ss1 << error;
    ss2 << value;
    std::cout << "value " << value << ", error" << error << std::endl;
    SmartDashboard::PutString("debug_procedure", "Value: " + ss2.str() + ", Error: " + ss1.str());
  }

};

START_ROBOT_CLASS(Robot)
