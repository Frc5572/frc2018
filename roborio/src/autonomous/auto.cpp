#include "auto.h"
#include "../drivetrain/drivetrain.h"
#include "match_data.h"
#include "../util/cpreprocessor.h"
#include <WPILib.h>
#include "../clothoid.h"

#define SLIPPING_MULTIPLIER .8

// All auto calls use these variables, so I condensed them into a single define
#define ALL_THE_VARS robot, drive, left, right, axle_width, WHEEL_CONSTANT, CURVE_P, intake_f, lift_f

#define MIN_VELOCITY .4

#define OUTTAKE_V (-.25)
#define LIFT_START_V 0.3
#define LIFT_V 0.8

#include "autotools.h"

/*
 *  AUTO MODE DEFINITIONS
 */

AUTO_FUNC(Straight, .45, (),(), (), 0, 100);

AUTO_FUNC(P2toSwL5, .4, (),
		(),(intake_f(2.0 * (OUTTAKE_V), .4);),
		0, 30)

AUTO_FUNC(P2toSwL4, .4, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(true, LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); P2toSwL5(ALL_THE_VARS);),
		25, -25,
		0, -10)

AUTO_FUNC(P2toSwL3, .55, (),
		(),(drive.set(-.5, -.5);intake_f(-3.0 * (OUTTAKE_V),2.0);drive.set(0, 0); P2toSwL4(ALL_THE_VARS);),
		20, 20,
		0, 10)

AUTO_FUNC(P2toSwL2, .4, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(0.1);P2toSwL3(ALL_THE_VARS);),
		0, -45)

CLOTH_FUNC(P2toSwL, .34,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) {

		if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); }

		} lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); }); Wait(1.0);),
		(t.join();),(t.join();drive.set(-.35, -.35);Wait(.1);intake_f(OUTTAKE_V,0.8);Wait(.8);drive.set(0, 0);P2toSwL2(ALL_THE_VARS);),
		-40, 20,
		40, 20,
		0, 65);


AUTO_FUNC(P2toSwR7,.45,  (), (), (drive.set(-.4, -.4); Wait(.25); intake_f(OUTTAKE_V,0.8);),
		12, 60);

AUTO_FUNC(P2toSwR6, .45, (), (), (P2toSwR7(ALL_THE_VARS);),
		-10, -20);

AUTO_FUNC(P2toSwR5, .45, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(true, LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });), (t.join();),(t.join();P2toSwR6(ALL_THE_VARS);),
		0, -20);

AUTO_FUNC(P2toSwR4, .45, (), (), (drive.set(-.2, -.2); intake_f(-3.0*OUTTAKE_V,0.8); intake_f(-3.0*OUTTAKE_V,0.8); P2toSwR5(ALL_THE_VARS);),
		-20, 40);

AUTO_FUNC(P2toSwR2,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join();Wait(.2);P2toSwR4(ALL_THE_VARS);),
		0, -65);

AUTO_FUNC(P2toSwR,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ lift_f(false, LIFT_V); } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); drive.set(-.25, -.25); Wait(0.5); intake_f(OUTTAKE_V,0.8); drive.set(0, 0); P2toSwR2(ALL_THE_VARS);),
		0, 65);

AUTO_FUNC(P3toSwR3, .45, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.2); drive.set(-.3, -.3); intake_f(-3.0*OUTTAKE_V,0.9); drive.set(.25, .25); intake_f(-3.0*OUTTAKE_V,0.4);drive.set(0, 0);
std::thread t2([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(true, LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t2.join(); drive.set(-.25, -.45); Wait(.7); intake_f(OUTTAKE_V,0.8);drive.set(0, 0);),
		15, -15,
		0, -50,
		12.5, 30)

AUTO_FUNC(P3toSwR2,.45,  (), (), (drive.set(-.3, -.3); intake_f(OUTTAKE_V,0.8); P3toSwR3(ALL_THE_VARS);),
		-15, 15)

AUTO_FUNC(P3toSwR,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ if(lift_f(false, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.3); P3toSwR2(ALL_THE_VARS);),
		0, 120);

AUTO_FUNC(P3toScR3,.65,
		(drive.set(.3, .3); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0);std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(lift_f(true, LIFT_V)) break; } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); intake_f(2.25*OUTTAKE_V, 0.8);),
		-20, -40,
		20, 25,
		-5, 25);

AUTO_FUNC(P3toScR2,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3.0) {  lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.2); drive.set(-.3, -.5); intake_f(-4.0*OUTTAKE_V,2.0); drive.set(0, 0); P3toScR3(ALL_THE_VARS);),
		20, -20,
		0, -10,
		-19, 30
		);

AUTO_FUNC(P3toScR,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); intake_f(1.25*OUTTAKE_V, 0.4); P3toScR2(ALL_THE_VARS);),
		0, 140,
		-16, 83);

AUTO_FUNC(P3toScRtoSwR3,.65,
		(drive.set(-.3, -.3); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0);std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { if(lift_f(true, LIFT_V)) break; } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); drive.set(-.6, -.4); Wait(0.4); drive.set(-.2, -.2); Wait(0.2); intake_f(OUTTAKE_V, 0.8);),
		0, -10);

AUTO_FUNC(P3toScRtoSwR2,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3.0) {  lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join();Wait(.2); drive.set(-.2, -.2); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0); P3toScRtoSwR3(ALL_THE_VARS);),
		40, -40,
		-35, 22);

AUTO_FUNC(P3toScRtoSwR,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); drive.set(-.3, -.45); Wait(.4); drive.set(0, 0);intake_f(1.25*OUTTAKE_V, 0.8); P3toScRtoSwR2(ALL_THE_VARS);),
		0, 140,
		-16, 83);

AUTO_FUNC(P3toScL2,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 0.2){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });t.join();),
		(),(drive.set(-.3, -.3); Wait(.3); drive.set(0, 0); intake_f(OUTTAKE_V, 2.0);),
		0,45,25,20);

AUTO_FUNC(P3toScL,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(false, LIFT_START_V); } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join();P3toScL2(ALL_THE_VARS);),
		20, 170,
		-56, 30,
		7, 94);

/**/


AUTO_FUNC(P1toSwL3, .45, (std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.2); drive.set(-.3, -.3); intake_f(-3.0*OUTTAKE_V,0.9); drive.set(.25, .25); intake_f(-3.0*OUTTAKE_V,0.4);drive.set(0, 0);
std::thread t2([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { lift_f(true, LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); }); t2.join(); drive.set(-.25, -.45); Wait(.7); intake_f(OUTTAKE_V,0.8);drive.set(0, 0);),
		-15, -15,
		-0, -50,
		-12.5, 30)

AUTO_FUNC(P1toSwL2,.45,  (), (), (drive.set(-.5, -.25); Wait(.5);intake_f(OUTTAKE_V,0.8); P1toSwL3(ALL_THE_VARS);),
		15, 15)

AUTO_FUNC(P1toSwL,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.5) { if(timer.Get() > 1.5){ if(lift_f(false, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.3); P1toSwL2(ALL_THE_VARS);),
		-0, 120);

AUTO_FUNC(P1toScL3,.65,
		(drive.set(.3, .3); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0);std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(lift_f(true, LIFT_V)) break; } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); intake_f(2.25*OUTTAKE_V, 0.8);),
		20, -40,
		-17, 35);

AUTO_FUNC(P1toScL2,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3.0) {  lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); Wait(.2); drive.set(-.3, -.5); intake_f(-4.0*OUTTAKE_V,2.0); drive.set(0, 0); P1toScL3(ALL_THE_VARS);),
		-20, -20,
		-5, -10,
		5, 30
		);

AUTO_FUNC(P1toScL,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); intake_f(OUTTAKE_V, 0.4); P1toScL2(ALL_THE_VARS);),
		0, 140,
		21, 83);

AUTO_FUNC(P1toScLtoSwL3,.65,
		(drive.set(.3, .3); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0); std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 1.5) { if(lift_f(true, LIFT_V)) break; } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); drive.set(-.6, -.4); Wait(0.4); drive.set(-.2, -.2); Wait(0.2); intake_f(OUTTAKE_V, 0.8);),
		0, -10);

AUTO_FUNC(P1toScLtoSwL2,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 3.0) {  lift_f(true, -LIFT_V); } lift_f(true, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join();Wait(.2); drive.set(-.2, -.4); intake_f(-3.0*OUTTAKE_V,0.4); drive.set(0, 0); P1toScLtoSwL3(ALL_THE_VARS);),
		-20, -20,
		-5, -10,
		5, 30);

AUTO_FUNC(P1toScLtoSwL,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 1.5){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join(); drive.set(-.3, -.45); Wait(.4); drive.set(0, 0);intake_f(1.25*OUTTAKE_V, 0.8); P1toScLtoSwL2(ALL_THE_VARS);),
		0, 140,
		21, 83);

AUTO_FUNC(P1toScR2,.45,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(true) { if(timer.Get() > 0.2){ if(lift_f(true, LIFT_V)) break; } else { lift_f(false, LIFT_START_V); } } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });t.join();),
		(),(drive.set(-.3, -.3); Wait(.3); drive.set(0, 0); intake_f(OUTTAKE_V, 2.0);),
		0,45,
		-25,20);

AUTO_FUNC(P1toScR,.65,
		(std::thread t([&]() { frc::Timer timer; SmartDashboard::PutNumber("Auto Seq",0);timer.Start(); while(timer.Get() < 2.0) { lift_f(false, LIFT_START_V); } lift_f(false, 0.0); SmartDashboard::PutNumber("Auto Seq",1); });),
		(t.join();),(t.join();P3toScL2(ALL_THE_VARS);),
		-20, 170,
		56, 30,
		-7, 94);

/*
 * AUTO START LOGIC
 */


void auto_setup() {
	std::thread t([](){

	});
	t.detach();
}

unsigned position = 2;

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
	if(position == 3){
		if(!leftswitch && !leftscale){
			P3toScRtoSwR(ALL_THE_VARS);
		}else if (!leftswitch) {
			P3toSwR(ALL_THE_VARS);
		} else if(!leftscale) {
			P3toScR(ALL_THE_VARS);
		} else {
			P3toScL(ALL_THE_VARS);
		}
	} else if(position == 2){
		if(leftswitch){
			P2toSwL(ALL_THE_VARS);
		} else {
			P2toSwR(ALL_THE_VARS);
		}
	} else if(position == 1){
		if(leftswitch && leftscale){
			P1toScLtoSwL(ALL_THE_VARS);
		}else if (leftswitch) {
			P1toSwL(ALL_THE_VARS);
		} else if(leftscale) {
			P1toScL(ALL_THE_VARS);
		} else {
			P1toScR(ALL_THE_VARS);
		}
	}
}
