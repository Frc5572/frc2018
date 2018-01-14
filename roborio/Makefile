AT = @
INCDIR = -I$(HOME)/wpilib/cpp/current/include -I$(HOME)/wpilib/user/cpp/include
CPPFLAGS += -g -Wall -W $(INCDIR) -std=c++14 -fPIC 
LFLAGS = -L$(HOME)/wpilib/cpp/current/lib -L$(HOME)/wpilib/user/cpp/lib -lCTRLib -lwpi
CXX = arm-frc-linux-gnueabi-g++
TEAM = 5572
RMCOMMAND = rm -f
DEPLOYTARGET = roboRIO-$(TEAM)-FRC.local

SOURCES = ${shell find src -name '*.cpp'}
HEADERS = ${shell find src -name '*.hpp'}
OBJECTS = $(patsubst src/%.cpp,bin/%.o,$(SOURCES))



all: dirs $(OBJECTS)
	test -d bin/ || mkdir -p bin/
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o FRCUserProgram
	rm bin/* -rf

dirs : 
	mkdir -p ${subst src,bin,${shell find src -type d}}
	

bin/%.o : src/%.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/*

doc :
	doxygen Doxyfile
	make -C latex