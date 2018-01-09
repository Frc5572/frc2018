#include "utils/cpreprocessor.h"
#include "drivetrain.h"

#include <iostream>

int main(){
  auto x = curveamount(5*HALF_PI, 2.5*HALF_PI, 5);
  std::cout << x.x << "," << x.y << " (" << x.heading << ")" << std::endl;
  return 0;
}
