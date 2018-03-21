#include "auto_follower.h"
#include <cmath>

std::pair< double, double > auto_follower::kinematics(double linear, double angular, double wheelbase) {
  double vl = linear - wheelbase * angular * 0.5;
  double vr = 2 * linear - vl;
  return {vl, vr};
}

double auto_follower::Path::solve(auto_follower::State state, double v) {
  double r = sqrt((state.x - m_state.x) * (state.x - m_state.x) + (state.y - m_state.y) * (state.y - m_state.y));
  double angle_to_state = atan2(m_state.y - state.y, m_state.x - state.x);
  double delta = state.theta - angle_to_state;
  double theta = state.theta - m_state.theta;
  return -v/r * (m_k2 * (delta - atan(-m_k1 * theta)) + (1.0 + (m_k1) / (1.0 + (m_k1 * theta) * (m_k1 * theta))) * sin(delta));
}

void auto_follower::Position_Tracker::update(double left, double right){
  if(left == right){
	state.x += left * cos(state.theta);
	state.y += left * sin(state.theta);
	return;
  }
  // Local
  double L1 = left > right ? right : left;
  double L2 = left < right ? right : left;
  double delta = (2.0 * (L2 - L1) - m_track * M_PI) / (2.0 * m_track);
  double r = m_track * .5 * (L2 + L1)/(L2 - L1);
  double y = (left > right ? -1.0 : 1.0) * (r + r * sin(delta));
  double x = r * cos(delta);
  // Global
  state.x += x * cos(state.theta) - y * sin(state.theta);
  state.y += y * cos(state.theta) + x * sin(state.theta);
  state.theta += ( L2 - L1 ) / m_track;
}
