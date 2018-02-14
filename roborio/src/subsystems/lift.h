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


#endif
