#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

#include <nodejs/src/node.h>
#include "drivetrain/drivetrain.h"

namespace watson {
  
  using namespace v8;
  using node::AtExit;
  
  std::string convert(Local<Value> s) {
    return std::string(*v8::String::Utf8Value(s->ToString()));
  }
  
  Local<String> convert(Isolate *isolate, std::string s) {
    return String::NewFromUtf8(isolate, s.c_str());
  }
  
  void aexit(void*){
    
  }
  
  void tbaget(const FunctionCallbackInfo<Value>& args){
    
  }
  
  

  void init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(exports, "tba", tbaget);
    AtExit(aexit);
  }

NODE_MODULE(NODE_GYP_MODULE_NAME, init)
  
};