#ifndef MATCH_DATA_H_
#define MATCH_DATA_H_

#include <string>

namespace field {
  
  namespace side {
  
    const bool left = false;
    const bool right = true;
  
    static bool set = false;
  
    static bool m_far, m_near, m_scale;
  
    inline void setup(){
      if(set) return;
      std::string gsm = "";//frc::DriverStation::GetInstance().GetGameSpecificMessage();
      auto x = [&](unsigned i){
        char gd = gsm[i];
        switch (gd) {
        case 'L':
        case 'l':
          return left;
        case 'R':
        case 'r':
          return right;
        default:
          return left;
        }
      };
      m_near = x(0);
      m_scale = x(1);
      m_far = x(2);
      set = true;
    }
  
    inline bool switch_near(){
      setup();
      return m_near;
    }
  
    inline bool switch_far(){
      setup();
      return m_far;
    }
  
    inline bool scale(){
      setup();
      return m_scale;
    }
  
  }
  
}

#endif