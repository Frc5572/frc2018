#include <iostream>
#include <memory>
#include <string>

#include <SampleRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Encoder.h>

#include "drivetrain/drivetrain.h"
#include "controller.h"

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

	bool curve(double x, double y, double maxV) {
		drivetrain::differential_curve dc(x, y, 27.8125);
		if (~dc) {
			std::cout << "Turning Right " << -dc << std::endl;
			if (fabs(-dc) <= fabs(right.GetRaw()) / WHEEL_CONSTANT) {
				return true;
			}
			drive.set(
					.3
							* (dc() * left.GetRaw() / WHEEL_CONSTANT
									- right.GetRaw() / WHEEL_CONSTANT), maxV);
		} else {
			std::cout << "Turning Left " << -dc << std::endl;
			if (fabs(-dc) <= fabs(left.GetRaw()) / WHEEL_CONSTANT) {
				return true;
			}
			drive.set(maxV,
					maxV * .5 * (dc() * right.GetRaw() / WHEEL_CONSTANT
									- left.GetRaw() / WHEEL_CONSTANT));
		}
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
		while (IsAutonomous() && IsEnabled() && !curve(-36, 36, .45)) {
			SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
			SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
		}
		drive.set(0, 0);
		left.Reset();
		right.Reset();
		Wait(0.5);
		//*
		while (IsAutonomous() && IsEnabled() && !straight(24, .45)) {
			SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
			SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
		}
		//*/
		drive.set(0, 0);
		left.Reset();
		right.Reset();
		Wait(0.5);
		while (IsAutonomous() && IsEnabled() && !curve(36, 36, .45)) {
			SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
			SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
		}
		drive.set(0, 0);
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
