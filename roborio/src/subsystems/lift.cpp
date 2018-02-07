#include "lift.h"

using namespace lift;

void init()
{
	*intake0 = VictorSP(/* Channel */);
	*intake1 = VictorSP(/* Channel */);
}

void update(FRC5572Controller A, FRC5572Controller B)
{
	intake0->Set(speedmax  * B.R());
	intake1->Set(-speedmax * B.R());
}

void exit()
{

}
