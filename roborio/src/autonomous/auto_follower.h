/**
 * @file auto_follower.h
 * @brief Controller for following a path autonomously
 * @author Wilson Watson
 * @date 19/3/2018
 */

#ifndef AUTO_FOLLOWER_H_
#define AUTO_FOLLOWER_H_

#include <vector>

namespace auto_follower {
  
  /**
   * @struct State
   * 
   */
  struct State {
    double x, y, theta;
  };
  
  /**
   * @class Path
   * 
   */
  class Path {
  public:
    /**
     * @brief Constructor
     * @param state State for the robot to run through
     */
    inline Path(State state, double k1, double k2) : m_state(state), m_k1(k1), m_k2(k2) {}
    /**
     * @brief Destructor
     */
    inline ~Path() {}
    /**
     * @brief Solve
     * @param state current position and angle
     * @param velocity desired velocity
     * @returns angular velocity
     */
    double solve(State state, double velocity);
  private:
    State m_state;
    double m_k1, m_k2;
  };
  
  /**
   * @brief Convert kinematics 
   * @param linear forward speed of the robot
   * @param angular turning speed of the robot
   */
  std::pair<double, double> kinematics(double linear, double angular, double wheelbase);
  
  /**
   * @class Position_Tracker
   * @brief Tracks position of the robot given encoder readings
   */
  class Position_Tracker {
  public:
    /**
     * @brief Initializes track variable
     * @param track 
     */
    inline Position_Tracker(const double track) : m_track(track) {}
    /**
     * @brief Deconstructor
     */
    inline ~Position_Tracker() {}
    /**
     * @brief Gets current state of the robot
     */
    inline State get_state(){
      return state;
    }
    /**
     * @brief Updates current position 
     * @param left distance of left encoder since last update step
     * @param right distance of right encoder since last update step
     */
    void update(double left, double right);
  private:
    State state;
    const double m_track;
  };
  
};

#endif