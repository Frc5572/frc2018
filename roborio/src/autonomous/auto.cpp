#include "auto.h"
#include "../drivetrain/drivetrain.h"
#include "match_data.h"
#include "../util/cpreprocessor.h"

#define SLIPPING_MULTIPLIER .8

#define MAX_VELOCITY .45
#define MIN_VELOCITY .4

#define __AUTO_FUNC(i, k, v1, v2) drivetrain::differential_curve EVAL1(DEFER1(PRIMITIVE_CAT)(dc, i))(v1, v2, axle_width);

#define _AUTO_FUNC(i, k, v1, v2) while (robot->IsAutonomous() && robot->IsEnabled()\
			&& !drivetrain::driveto(drive, EVAL1(DEFER1(PRIMITIVE_CAT)(dc, i)), \
					fabs(left.GetRaw() / WHEEL_CONSTANT),\
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,\
					max_velocity = -MAX_VELOCITY, min_velocity = -MIN_VELOCITY)) {\
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);\
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);\
	}\
	SmartDashboard::PutNumber("Auto_Seq", i);\
	drive.set(0, 0);\
	left.Reset();\
	right.Reset();\
	Wait(0.5);

#define AUTO_FUNC(name, end, ...) void name(frc::RobotBase *robot, drivetrain::differential_drive& drive,\
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,\
		double CURVE_P, void (*intake_f)(double)) {VA_ITER_2(__AUTO_FUNC, (), __VA_ARGS__);VA_ITER_2(_AUTO_FUNC, (), __VA_ARGS__); EXPAND end}

AUTO_FUNC(P1toSwRx, (intake_f(-.25);),
		48.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER,
		0 * SLIPPING_MULTIPLIER, 36 * SLIPPING_MULTIPLIER,
		-48.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER
); //TODO: switch all the functions below to this form

void P1toSwR(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(48.5 * SLIPPING_MULTIPLIER,
			48.5 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc1(0, 36 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc2(-48.5 * SLIPPING_MULTIPLIER,
			48.5 * SLIPPING_MULTIPLIER, axle_width);
	SmartDashboard::PutNumber("Auto_Seq", 0);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc1,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc2,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 3);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	intake_f(-.25);
}

void P1toSwL(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(0, 95 * SLIPPING_MULTIPLIER, axle_width);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	intake_f(-.25);
}

void P2toSwL(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(-48.5 * SLIPPING_MULTIPLIER,
			48.5 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc1(0, 36 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc2(48.5 * SLIPPING_MULTIPLIER,
			48.5 * SLIPPING_MULTIPLIER, axle_width);
	SmartDashboard::PutNumber("Auto_Seq", 0);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc1,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc2,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 3);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	intake_f(-.25);
}

void P2toSwR(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(0, 90 * SLIPPING_MULTIPLIER, axle_width);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	intake_f(-.25);
}

void P3toSwR(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(-20, 90 * SLIPPING_MULTIPLIER,
			axle_width);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	left.Reset();
	right.Reset();
	Wait(0.5);
	intake_f(-.3);
}

void P3toSwL(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {
	drivetrain::differential_curve dc(0 * SLIPPING_MULTIPLIER,
			170 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc1(-45 * SLIPPING_MULTIPLIER,
			45 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc2(0 * SLIPPING_MULTIPLIER,
			70 * SLIPPING_MULTIPLIER, axle_width);
	drivetrain::differential_curve dc3(36 * SLIPPING_MULTIPLIER,
			36 * SLIPPING_MULTIPLIER, axle_width);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc1,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc2,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
	while (robot->IsAutonomous() && robot->IsEnabled()
			&& !drivetrain::driveto(drive, dc3,
					fabs(left.GetRaw() / WHEEL_CONSTANT),
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,
					max_velocity = -0.45, min_velocity = -.4)) {
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);
	}
	SmartDashboard::PutNumber("Auto_Seq", 1);
	drive.set(0, 0);
	Wait(0.5);
	left.Reset();
	right.Reset();
}

/*
 double axle_width = 25;
 double max_speed = .45;
 double min_speed = .3;

 drivetrain::differential_curve dc0(36, 71, axle_width);
 drivetrain::differential_curve dc1(-103.7732365472621, 32.63610541265586, axle_width);


 while (robot->IsAutonomous() && robot->IsEnabled() && !drivetrain::driveto(drive, dc0, left.GetRaw() / WHEEL_CONSTANT, right.GetRaw() / WHEEL_CONSTANT, curve_p = CURVE_P, max_velocity = max_speed, min_velocity = min_speed)) {

 }
 reset();

 while (robot->IsAutonomous() && robot->IsEnabled() && !drivetrain::driveto(drive, dc1, left.GetRaw() / WHEEL_CONSTANT, right.GetRaw() / WHEEL_CONSTANT, curve_p = CURVE_P, max_velocity = max_speed, min_velocity = min_speed)) {

 }
 reset();


 */

void auto_run(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double)) {

	P3toSwL(robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P,
			intake_f);

	return;

	unsigned mode = 0; // 0, 6 - Desired position left or right. 0, 3 - Switch or Scale. 1, 2, 4, 5 - Robot Position. Lower being left.

	// TODO: get data from shuffleboard

	MatchData::OwnedSide side = MatchData::get_owned_side(
			MatchData::GameFeature::SWITCH_NEAR);
	while (side == MatchData::OwnedSide::UNKNOWN)
		if (!robot->IsAutonomous())
			return; // Wait until driver station tells us where we are. Or quit because it won't tell us until after auto.
	if (side == MatchData::OwnedSide::RIGHT) { // Add 6 if on the desired side is on the right
		mode += 6;
	}

}
