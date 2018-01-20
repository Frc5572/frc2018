#include "drivetrain.h"

void drivetrain::differential_drive::set(double l, double r){
  for(unsigned i = 0; i < left.size(); i++){
    left[i]->Set(l);
  }
  for(unsigned i = 0; i < right.size(); i++){
    right[i]->Set(-r);
  }
}
