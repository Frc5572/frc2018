#include "drivetrain.h"

//#define COUNTER_CLOCKWISE

void drivetrain::differential_drive::set(double l, double r){
  for(unsigned i = 0; i < left.size(); i++){
    left[i]->Set(
#ifdef COUNTER_CLOCKWISE
      -
#endif
      l);
  }
  for(unsigned i = 0; i < right.size(); i++){
    right[i]->Set(
#ifndef COUNTER_CLOCKWISE
      -
#endif
      r);
  }
}