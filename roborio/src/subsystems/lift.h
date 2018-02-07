#ifndef LIFT_H_
#define LIFT_H_

#include "../input/controller.h"
#include "WPILib.h"

namespace lift
{

	void init();

	void update(FRC5572Controller A, FRC5572Controller B);

	void exit();

}

extern frc::VictorSP *intake0;
extern frc::VictorSP *intake1;

extern int speedmax = 0.5;


#endif
