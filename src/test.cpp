#include "utils/cpreprocessor.h"
#include "drivetrain.h"

#include <iostream>

int main(){
  auto x = curveamount(0, 5*HALF_PI, 5);
  x = x + curveamount(5*HALF_PI, 0, 5);
  std::cout << x.x << "," << x.y << " (" << x.heading << ")" << std::endl;
  return 0;
}
