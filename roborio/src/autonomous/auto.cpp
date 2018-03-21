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

AUTO_FUNC(Straight, (), (), 5 * SLIPPING_MULTIPLIER, 100 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P2toSwL,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) {

		if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); }

		} lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(drive.set(-.2, -.2);Wait(.4);intake_f(OUTTAKE_V);t.join();),
		-50 * SLIPPING_MULTIPLIER, 50 * SLIPPING_MULTIPLIER, 0,
		30 * SLIPPING_MULTIPLIER, 25 * SLIPPING_MULTIPLIER,
		25 * SLIPPING_MULTIPLIER, 0, 25 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P2toSwR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); drive.set(-.25, -.25); Wait(0.15); intake_f(OUTTAKE_V); drive.set(0, 0);), 0, 65 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P3toSwR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ if(lift_f(false, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t.join();),
		(intake_f(OUTTAKE_V);), 0, 120 * SLIPPING_MULTIPLIER,
		15 * SLIPPING_MULTIPLIER, 15 * SLIPPING_MULTIPLIER);

AUTO_FUNC(P3toScR,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join(); drive.set(-.3, -.3); Wait(.4); drive.set(0, 0);intake_f(OUTTAKE_V);),
		10 * SLIPPING_MULTIPLIER, 140 * SLIPPING_MULTIPLIER,
		-20 * SLIPPING_MULTIPLIER, 80 * SLIPPING_MULTIPLIER);

/*
 * AUTO START LOGIC
 */


void auto_setup() {
	std::thread t([](){

	});
}

void auto_run(frc::RobotBase *robot, drivetrain::differential_drive& drive,
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,
		double CURVE_P, void (*intake_f)(double),
		bool (*lift_f)(bool, double)) {
// All auto calls use these variables, so I condensed them into a single define
#define ALL_THE_VARS robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f

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
