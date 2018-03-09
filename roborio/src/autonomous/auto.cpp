#include "auto.h"
#include "../drivetrain/drivetrain.h"
#include "match_data.h"
#include "../util/cpreprocessor.h"
#include <WPILib.h>

#define SLIPPING_MULTIPLIER .8
//#define SLIPPING_MULTIPLIER .67

#define MAX_VELOCITY .45
#define MIN_VELOCITY .4

#define OUTTAKE_V -.25
#define LIFT_START_V 0.2
#define LIFT_V 0.4
/*
#define OUTTAKE_V -0.4
#define LIFT_START_V 0.2
#define LIFT_V 0.4
*/
#define __AUTO_FUNC(i, k, v1, v2) drivetrain::differential_curve PRIMITIVE_CAT(dc, i)(v1, v2 > 0 ? v2 : -v2, axle_width);

#define _AUTO_FUNC(i, k, v1, v2) while (robot->IsAutonomous() && robot->IsEnabled()\
			&& !drivetrain::driveto(drive, PRIMITIVE_CAT(dc, i), \
					fabs(left.GetRaw() / WHEEL_CONSTANT),\
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,\
					max_velocity = -MAX_VELOCITY * (v2 > 0 ? 1 : -1), min_velocity = -MIN_VELOCITY * (v2 > 0 ? 1 : -1))) {\
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);\
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);\
	}\
	SmartDashboard::PutNumber("Auto_Seq", i);\
	drive.set(0, 0);\
	if(v1 == v2){left.Reset(); right.Reset();}\
	Wait(0.5);\
	if(v1 != v2){left.Reset(); right.Reset();}

#define AUTO_FUNC(name, start, end, ...) void name(frc::RobotBase *robot, drivetrain::differential_drive& drive,\
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,\
		double CURVE_P, void (*intake_f)(double), bool (*lift_f)(double)) {EXPAND start;\
left.Reset();\
right.Reset();\
VA_ITER_2(__AUTO_FUNC, (), __VA_ARGS__);VA_ITER_2(_AUTO_FUNC, (), __VA_ARGS__); EXPAND end}

/*

 AUTO_FUNC(P1toSwR,
 (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3) {

 if(timer.Get() > 1.5){ if(lift_f(LIFT_V)) break; } else { lift_f(LIFT_START_V); }

 } lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
 (intake_f(OUTTAKE_V); t.join();), 48.5 * SLIPPING_MULTIPLIER,
 48.5 * SLIPPING_MULTIPLIER, 0, 36 * SLIPPING_MULTIPLIER,
 -48.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P2toSwR, (), (intake_f(OUTTAKE_V);), 0, 90 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P3toSwR, (), (intake_f(OUTTAKE_V);), -20, 90 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toScL2,
 (),
 (), 0 * SLIPPING_MULTIPLIER,
 -20 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toScL,
 (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 13) { if(timer.Get() > 3){ if(lift_f(LIFT_V)) break; } else { lift_f(0.2); } } lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
 (t.join();intake_f(OUTTAKE_V);P1toScL2(robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f);), -20.0 * SLIPPING_MULTIPLIER,
 48.5 * SLIPPING_MULTIPLIER, 20.5 * SLIPPING_MULTIPLIER,
 48.5 * SLIPPING_MULTIPLIER, 0, 50 * SLIPPING_MULTIPLIER,
 40 * SLIPPING_MULTIPLIER, 105 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P3toScR2,
 (),
 (), 0 * SLIPPING_MULTIPLIER,
 -20 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P3toScR,
 (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 13) { if(timer.Get() > 3){ if(lift_f(LIFT_V)) break; } else { lift_f(0.2); } } lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
 (t.join();intake_f(OUTTAKE_V);P1toScL2(robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f);),
 0, 147.0 * SLIPPING_MULTIPLIER,
 -40 * SLIPPING_MULTIPLIER, 105 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toScR3, (), (intake_f(OUTTAKE_V);), -30 * SLIPPING_MULTIPLIER,
 20 * SLIPPING_MULTIPLIER, -2 * SLIPPING_MULTIPLIER,
 3 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toScR2,
 (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 8) { if(lift_f(LIFT_V)) break; } lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
 (t.join(); P1toScR3(robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f);),
 0, 130 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toScR,
 (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(LIFT_START_V); } lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
 (t.join();P1toScR2(robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f);),
 -20.0 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER,
 20.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER, 0,
 80 * SLIPPING_MULTIPLIER, 19.7 * SLIPPING_MULTIPLIER,
 20 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P1toSwL, (), (intake_f(OUTTAKE_V);), 0, 95 * SLIPPING_MULTIPLIER);

 AUTO_FUNC(P2toSwL, (), (intake_f(OUTTAKE_V);), -48.5 * SLIPPING_MULTIPLIER,
 48.5 * SLIPPING_MULTIPLIER, 0, 36 * SLIPPING_MULTIPLIER,
 48.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER);

 */

/* Switch Left */

AUTO_FUNC(P1toSwL, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2) {

	if(timer.Get() > 1.5){ if(lift_f(LIFT_V)) break; } else { lift_f(LIFT_START_V); }

	} lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t.join();), (intake_f(OUTTAKE_V);), 20, 90 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P2toSwL,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 4) {

		if(timer.Get() > 1.5){ lift_f(LIFT_V); } else { lift_f(LIFT_START_V); }

		} lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(Wait(.4);intake_f(OUTTAKE_V);t.join();), -50 * SLIPPING_MULTIPLIER,
		50 * SLIPPING_MULTIPLIER, 0, 30 * SLIPPING_MULTIPLIER,
		25 * SLIPPING_MULTIPLIER, 25 * SLIPPING_MULTIPLIER, 0, 25 * SLIPPING_MULTIPLIER);

AUTO_FUNC(Straight, (), (), 0, 100 * SLIPPING_MULTIPLIER); // Warning: This doesn't actually go to the switch.

/* Switch Right */

AUTO_FUNC(P1toSwR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3) {
		if(timer.Get() > 1.5){ if(lift_f(LIFT_V)) break; } else { lift_f(LIFT_START_V); }
		} lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(intake_f(OUTTAKE_V); t.join();), 48.5 * SLIPPING_MULTIPLIER,
		48.5 * SLIPPING_MULTIPLIER, 0, 36 * SLIPPING_MULTIPLIER,
		-48.5 * SLIPPING_MULTIPLIER, 48.5 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P2toSwR, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 4) {
	if(timer.Get() > 1.5){ lift_f(LIFT_V); } else { lift_f(LIFT_START_V); }
	} lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t.join();), (intake_f(OUTTAKE_V);), 0, 100 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P3toSwR, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 4) {
	if(timer.Get() > 1.5){ if(lift_f(LIFT_V)) break; } else { lift_f(LIFT_START_V); }
	} lift_f(0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t.join();), (intake_f(OUTTAKE_V);), -20, 90 * SLIPPING_MULTIPLIER);

std::string current_auto = "";

void auto_setup() {
	while(SmartDashboard::GetString("Starting Position", "") != "")
		SmartDashboard::PutString("Starting Position", "");
	std::thread t(
			[&]() {
				while(true) {
					current_auto = SmartDashboard::GetString("Starting Position", "");
					if(current_auto.length() > 1)
						SmartDashboard::PutString("Auto Preference", std::string(current_auto[0] == '1' ? "Left" : (current_auto[0] == '2' ? "Middle" : "Right")));;
				}
			});
	t.detach();
}

void auto_run(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double), bool (*lift_f)(double)) {

	uint8_t mode[4];

	mode[0] = current_auto[0] == '1' ? 0 : (current_auto[0] == '3' ? 2 : 1);
	mode[1] = 0;

	SmartDashboard::PutString("Starting Position", "");

	while (MatchData::get_owned_side(MatchData::GameFeature::SWITCH_NEAR)
			== MatchData::OwnedSide::UNKNOWN)
		if (!robot->IsAutonomous())
			return; // Wait until driver station tells us where we are. Or quit because it won't tell us until after auto.
	mode[2] = static_cast<uint8_t>(MatchData::get_owned_side(
			MatchData::GameFeature::SWITCH_NEAR));
	mode[3] = static_cast<uint8_t>(MatchData::get_owned_side(
			MatchData::GameFeature::SCALE));

	//if (mode[1] == 0) { // Switch
		if (mode[0] == 0) { // Left
			if (mode[2] == static_cast<uint8_t>(MatchData::OwnedSide::LEFT)) {
				Straight(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			} else {
				Straight(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			}
		} else if (mode[0] == 1) { // Middle
			middle: if (mode[2]
					== static_cast<uint8_t>(MatchData::OwnedSide::LEFT)) {
				P2toSwL(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			} else {
				P2toSwR(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			}
		} else { // Right
			if (mode[2] == static_cast<uint8_t>(MatchData::OwnedSide::LEFT)) {
				Straight(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			} else {
				P3toSwR(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
						CURVE_P, intake_f, lift_f);
			}
		}
	//}
	/*else { // Scale
	 if (mode[0] == 0) { // Left
	 if (mode[2] == static_cast<uint8_t>(MatchData::OwnedSide::LEFT)) {
	 P1toScL(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
	 CURVE_P, intake_f, lift_f);
	 } else {

	 }
	 } else if (mode[0] == 1) { // Middle
	 goto middle;
	 // Placeholder
	 } else { // Right
	 if (mode[2] == static_cast<uint8_t>(MatchData::OwnedSide::LEFT)) {

	 } else {
	 P3toScR(robot, drive, left, right, axle_width, WHEEL_CONSTANT,
	 CURVE_P, intake_f, lift_f);
	 }
	 }
	 }
	 */
}

/*
 These are old autonomous modes


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
 intake_f(OUTTAKE_V);
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
 intake_f(OUTTAKE_V);
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
 intake_f(OUTTAKE_V);
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
 intake_f(OUTTAKE_V);
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
 */
