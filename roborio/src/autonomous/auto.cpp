#include "auto.h"
#include "../drivetrain/drivetrain.h"
#include "match_data.h"
#include "../util/cpreprocessor.h"
#include <WPILib.h>

#define SLIPPING_MULTIPLIER .8
//#define SLIPPING_MULTIPLIER .67


// All auto calls use these variables, so I condensed them into a single define
#define ALL_THE_VARS robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f

#define MAX_VELOCITY .65
#define MIN_VELOCITY .4

#define OUTTAKE_V -.25
#define LIFT_START_V 0.3
#define LIFT_V 0.8
/*
 #define OUTTAKE_V -0.4
 #define LIFT_START_V 0.2
 #define LIFT_V 0.4
 */

#include "autotools.h"

/*
 *  AUTO MODE DEFINITIONS
 */

AUTO_FUNC(Straight, (), (), 0, 100);

AUTO_FUNC(P2toSwL,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) {

		if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); }

		} lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); }); Wait(.5);),
		(drive.set(-.2, -.2);Wait(.4);intake_f(OUTTAKE_V,0.8);t.join();),
		-50, 50,
		0, 30,
		25, 25,
		0, 25);


AUTO_FUNC(P2toSwR7, (), (intake_f(OUTTAKE_V,0.8);),
		0, 60);

AUTO_FUNC(P2toSwR6, (), (P2toSwR7(ALL_THE_VARS);),
		-10, -20);

AUTO_FUNC(P2toSwR5, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(true, LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });), (t.join();P2toSwR6(ALL_THE_VARS);),
		0, -20);

AUTO_FUNC(P2toSwR4, (), (drive.set(-.2, -.2); intake_f(-3.0*OUTTAKE_V,0.8); intake_f(-3.0*OUTTAKE_V,0.8); P2toSwR5(ALL_THE_VARS);),
		-20, 40);

AUTO_FUNC(P2toSwR2,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.0) { lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();Wait(.2);P2toSwR4(ALL_THE_VARS);),
		0, -65);

AUTO_FUNC(P2toSwR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); drive.set(-.25, -.25); Wait(0.3); intake_f(OUTTAKE_V,0.8); drive.set(0, 0); P2toSwR2(ALL_THE_VARS);),
		0, 65);

AUTO_FUNC(P3toSwR2, (), (intake_f(OUTTAKE_V,0.8);),
		-15, 15)

AUTO_FUNC(P3toSwR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ if(lift_f(false, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); Wait(.3); P3toSwR2(ALL_THE_VARS);),
		0, 120);

AUTO_FUNC(P3toScR4,
		(drive.set(-.3, -.3); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0);std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(lift_f(true, LIFT_V)) break; } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); intake_f(2.25*OUTTAKE_V, 0.8);),
		-50, -30,
		9, 45);

AUTO_FUNC(P3toScR2,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3.0) {  lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();Wait(.2); drive.set(-.2, -.2); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0); P3toScR4(ALL_THE_VARS);),
		20, -45,
		-50, 30);

AUTO_FUNC(P3toScR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); drive.set(-.3, -.45); Wait(.4); drive.set(0, 0);intake_f(1.25*OUTTAKE_V, 0.8); P3toScR2(ALL_THE_VARS);),
		10, 140,
		-20, 80);

/*
 * AUTO START LOGIC
 */


void auto_setup() {
	std::thread t([](){

	});
	t.detach();
}

void auto_run(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double, double),
		bool (*lift_f)(bool, double)) {

	while (MatchData::get_owned_side(MatchData::GameFeature::SWITCH_NEAR)
			== MatchData::OwnedSide::UNKNOWN)
		if (!robot->IsAutonomous())
			return; // Wait until driver station tells us where we are. Or quit because it won't tell us until after auto.
	bool leftscale = MatchData::get_owned_side(MatchData::GameFeature::SCALE)
				== MatchData::OwnedSide::LEFT;
	bool leftswitch = MatchData::get_owned_side(MatchData::GameFeature::SWITCH_NEAR)
				== MatchData::OwnedSide::LEFT;
	if (!leftscale) {
		P3toScR(ALL_THE_VARS);
	} else {
		Straight(ALL_THE_VARS);
	}
}
