#ifndef CLOTHOID_H_
#define CLOTHOID_H_

#include <vector>
#include <utility>

#include <cmath>

#include <iostream>


namespace clothoid {
  
  inline std::vector<std::pair<double, double>> solve(double x, double y, double c, double v, bool& success, std::vector<double>& angles,unsigned resolution = 50){
    bool flip = x > 0;
    x = x > 0 ? x : -x;
    std::vector<std::pair<double, double>> path;
    success = false;
    if(x == 0 || y == 0) return path; // not a clothoid
    success = true;
    double theta = 2.0 * atan2(x, y);
    // Calculate R (No solution to this yet)
    double R = x; // Radius in inches
    double L = v*v*v/(c*R);
    double maxL = sqrt(24 * R);
    if(maxL < L) // Not Okay
      return path;
    //double S = L*L/(24*R);
    // Offset Method using Cubic Parabola
    for(double i = 0; i <= L; i+= L / (resolution / 3.0 - 1)){
      // x = y^3/6RL
      path.push_back({i, (i*i*i)/(6.0*R*L)});
      angles.push_back((flip ? -1.0 : 1.0 ) * (i*i)/(2.0*L*R));
    }
    unsigned path_offset = path.size() - 1;
    double start_t = L / 2.0 / R;
    for(double i = (theta - 2.0 * start_t)/(resolution / 3.0 - 1); i < theta - 2 * start_t; i+= (theta - 2.0 * start_t)/(resolution / 3.0 - 1)){
      double x = R * sin(i);
      double vy = -R * cos(i)+R;
      path.push_back({path[path_offset].first + x * cos(start_t) - vy * sin(start_t), path[path_offset].second + vy * cos(start_t) + x * sin(start_t)});
      angles.push_back((flip ? -1.0 : 1.0 ) * (start_t + i));
    }
    unsigned arc_offset = path.size() - 1;
    start_t = theta - start_t;
    for(double i = L; i > 0; i-= L / (resolution / 3.0 - 1)){
      // x = y^3/6RL
      double x = L-i;
      double y = (i)*(i)*(i) / (6.0*R*L) - L*L/(6.0*R);
      path.push_back({path[arc_offset].first + x * cos(theta) - y * sin(theta), path[arc_offset].second + y * cos(theta) + x * sin(theta)});
      angles.push_back((flip ? -1.0 : 1.0 ) * (theta - L / 2.0 / R + (L-i)*(L-i) / (2.0*R*L)));
    }
    
    double multiplier_x = x / path[path.size() - 1].second;
    double multiplier_y = y / path[path.size() - 1].first;
    if(flip) multiplier_y = -multiplier_y;
    for(unsigned i = 0; i < path.size(); i++){
      path[i].first = path[i].first * multiplier_x;
      path[i].second = path[i].second * multiplier_y;
    }
    return path;
  };
  
  inline std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> solve_sides(double x, double y, double c, double v, double w, bool& success,unsigned resolution = 50){
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> ret;
    std::vector<std::pair<double, double>> path;
    
    std::vector<double> angles;
    path = solve(x, y, c, v, success, angles, resolution);
    
    if(!success){
      return ret;
    }
    
    double offset = w * 0.5;
    
    for(unsigned i = 0; i < path.size(); i++){
      double xoffset = offset * cos(angles[i] + M_PI / 2.0);
      double yoffset = offset * sin(angles[i] + M_PI / 2.0);
      ret.push_back({{path[i].first + xoffset, path[i].second + yoffset},{path[i].first - xoffset, path[i].second - yoffset}});
    }
    
    return ret;
  };
  


  inline std::vector<std::pair<double, double>> profile(double x, double y, double c, double v, double w, bool& success,unsigned resolution = 50){
    std::vector<std::pair<double, double>> prf;
    
    if(x == 0){
    	prf.push_back({y,y});
    	return prf;
    }

    if(!success) return prf;

    auto sol = solve_sides(x, y, c, v, w, success, resolution); // Get positions

    if(!success) return prf;
    
    double left_dist = 0;
    double right_dist = 0;
    
    auto sqr = [](double x){return x*x;};
    
    for(unsigned i = 1; i < sol.size(); i++){
      double dl = sqrt(sqr(sol[i].first.first - sol[i - 1].first.first) + sqr(sol[i].first.second - sol[i - 1].first.second));
      double dr = sqrt(sqr(sol[i].second.first - sol[i - 1].second.first) + sqr(sol[i].second.second - sol[i - 1].second.second));
      left_dist += dl;
      right_dist += dr;
      prf.push_back({left_dist, right_dist});
    }
    
    return prf;
  }
  
#define SLIPPING_MULTIPLIER .8

  template <typename T>
  inline bool follow(T drive, std::vector<std::pair<double, double>> dc, double startV, double endV, double ldist, double rdist, double curve_p, unsigned& index){
	ldist /= SLIPPING_MULTIPLIER;
	rdist /= SLIPPING_MULTIPLIER;
	if(dc.size() == 1 && dc[0].first == dc[0].second){ // Driving straight
    	double error = (startV > 0.0 ? 1.0 : -1.0 ) * (ldist - rdist) * curve_p;
    	drive.set(startV - error, startV + error);
    	if(fabs(ldist) >= dc[0].first) return true;
    	return false;
    }
	while(index < dc.size() && (dc[index].first < ldist && dc[index].second < rdist)){
      index++;
    }
    if(index == dc.size()) return true; // If we've finished the curve, stop using this
    // Reverse linear interpolate
    double lspeed = dc[index + 1].first - dc[index].first;
    double rspeed = dc[index + 1].second - dc[index].second;

    lspeed = lspeed > rspeed ? 1.0 : lspeed / rspeed; // Left speed multiplier
    rspeed = lspeed < rspeed ? 1.0 : rspeed / lspeed; // Right speed multiplier

    double speed;

    if(index + 1 == dc.size()) {

    	speed = endV;

    } else {
    	double interp = (double) index / (double) dc.size(); // Approximately how far through path
    	double interp_l = (ldist - dc[index].first) / (dc[index + 1].first - dc[index].first); // How far through left side of index
    	double interp_r = (rdist - dc[index].second) / (dc[index + 1].second - dc[index].second); // How far through right side of index
    	double next_interp = (double) (index + 1) / (double) dc.size(); // Approximately how far through path next index will be

    	double full_interpolate = std::min(interp_l, interp_r) * (next_interp - interp) + interp; // Set speed to interpolate furthest from endpoint

    	speed = full_interpolate * (endV - startV) + startV; // Interpolate speed from full_interpolate
    }

    double lerror = (dc[index+1].first - ldist) / lspeed;
    double rerror = (dc[index+1].second - rdist) / rspeed;

    if(lspeed + curve_p * lerror < 0) lspeed = 0;
    if(rspeed + curve_p * rerror < 0) rspeed = 0;

    if(lspeed == rspeed && lspeed == 0) return true;

    drive.set((lspeed < 0 ? 0.0 : 1.0) *  startV * (lspeed + curve_p * lerror), (lspeed < 0 ? 0.0 : 1.0) * startV * (rspeed + curve_p * rerror));

    return false;
  }
  
};

#endif
