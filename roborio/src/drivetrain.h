#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_

#include "WPILib.h"
#include <vector>

namespace drivetrain { // Robot drivetrain methods
	void init();
	void setMotors(std::vector<SpeedController*>, std::vector<SpeedController*>); // Set motor values
	template <typename T>
	void setMotors(std::vector<int> left, std::vector<int> right){
		std::vector<SpeedController*> l, r;
		for(unsigned i = 0; i < left.size(); i++){
			l.push_back(new T(left[i]));
		}
		for(unsigned i = 0; i < right.size(); i++){
			r.push_back(new T(right[i]));
		}
		setMotors(l, r);
	}
	void drive_tank(double, double, double); // Tank drive control
	void drive_lr(double, double, double = 1); // Left-Right drive control
}

#endif
