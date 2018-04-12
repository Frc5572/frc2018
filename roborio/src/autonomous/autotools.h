
#define __AUTO_FUNC(i, k, v1, v2) drivetrain::differential_curve PRIMITIVE_CAT(dc, i)(v1 * SLIPPING_MULTIPLIER, v2 > 0 ? v2 * SLIPPING_MULTIPLIER : -v2 * SLIPPING_MULTIPLIER, axle_width);

#define _AUTO_FUNC(i, k, v1, v2) while (robot->IsAutonomous() && robot->IsEnabled()\
			&& !drivetrain::driveto(drive, PRIMITIVE_CAT(dc, i), \
					fabs(left.GetRaw() / WHEEL_CONSTANT),\
					fabs(right.GetRaw() / WHEEL_CONSTANT), curve_p = CURVE_P,\
					max_velocity = -k * (v2 > 0 ? 1 : -1), min_velocity = -MIN_VELOCITY * (v2 > 0 ? 1 : -1))) {\
		SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);\
		SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);\
	}\
	SmartDashboard::PutNumber("Auto_Seq", i);\
	drive.set(0, 0);\
	if(v1 == v2){left.Reset(); right.Reset();}\
	Wait(0.5);\
	if(v1 != v2){left.Reset(); right.Reset();}

#define AUTO_FUNC(name, speed, start, critend, end, ...) void name(frc::RobotBase *robot, drivetrain::differential_drive& drive,\
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,\
		double CURVE_P, void (*intake_f)(double, double), bool (*lift_f)(bool, double)) {EXPAND start;\
left.Reset();\
right.Reset();\
VA_ITER_2(__AUTO_FUNC, (), __VA_ARGS__);\
VA_ITER_2(_AUTO_FUNC, (speed), __VA_ARGS__); EXPAND end}


#define __CLOTH_FUNC(i, k, v1, v2) auto PRIMITIVE_CAT(path, i) = clothoid::profile(v1, fabs(v2), 3, 10.0, axle_width, success);

#define _CLOTH_FUNC(i, k, v1, v2) while(robot->IsAutonomous() && robot->IsEnabled() && !clothoid::follow(drive, PRIMITIVE_CAT(path, i), (v2 < 0 ? 1.0 : -1.0) * k, (v2 < 0 ? 1.0 : -1.0) * .45, fabs(left.GetRaw()) / WHEEL_CONSTANT - loffset, fabs(right.GetRaw()) / WHEEL_CONSTANT - roffset, .3, index)){\
			frc::SmartDashboard::PutNumber("speed_diff", left.GetRate() - right.GetRate());\
			frc::SmartDashboard::PutNumber("left", left.GetRaw() / WHEEL_CONSTANT);\
			frc::SmartDashboard::PutNumber("right", right.GetRaw() / WHEEL_CONSTANT);\
		}\
		loffset += PRIMITIVE_CAT(path, i)[PRIMITIVE_CAT(path, i).size() - 1].first;\
		roffset += PRIMITIVE_CAT(path, i)[PRIMITIVE_CAT(path, i).size() - 1].second;\
		index = 0;


#define CLOTH_FUNC(name, speed, start, critical_end, end, ...) void name(frc::RobotBase *robot, drivetrain::differential_drive& drive,\
		Encoder& left, Encoder& right, double axle_width, double WHEEL_CONSTANT,\
		double CURVE_P, void (*intake_f)(double, double), bool (*lift_f)(bool, double)) {EXPAND start;\
left.Reset();\
		right.Reset();\
		bool success = true;\
		VA_ITER_2(__CLOTH_FUNC, (), __VA_ARGS__)\
		std::cout << success << std::endl;\
		if(!success) return;\
		unsigned index = 0;\
		double loffset = 0, roffset = 0;\
		VA_ITER_2(_CLOTH_FUNC, (speed), __VA_ARGS__); drive.set(0, 0); if(robot->IsAutonomous()){EXPAND end}else{EXPAND critical_end}}

