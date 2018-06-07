AT = @
INCDIR = -I$(HOME)/wpilib/cpp/current/include -I$(HOME)/wpilib/user/cpp/include
CPPFLAGS += -g -Wall -W $(INCDIR) -std=c++14 -fPIC 
LFLAGS = -L$(HOME)/wpilib/cpp/current/reflib/linux/athena/shared -L$(HOME)/wpilib/common/current/lib/linux/athena/shared -L$(HOME)/wpilib/user/cpp/lib -lwpi -lpthread
CXX = arm-frc-linux-gnueabi-g++
TEAM = 5572
RMCOMMAND = rm -f
DEPLOYTARGET = roboRIO-$(TEAM)-FRC.local

SOURCES = ${shell find src -name '*.cpp'}
HEADERS = ${shell find src -name '*.hpp'}
OBJECTS = $(patsubst %.cpp,Debug/%.o,$(SOURCES))

all: dirs $(OBJECTS)
	@test -d Debug/src/ || mkdir -p Debug/src/
	$(CXX) $(CPPFLAGS) $(OBJECTS) $(LFLAGS) -o FRCUserProgram

see:
	$(CXX) -E src/autonomous/auto.cpp $(CPPFLAGS) $(LFLAGS)

dirs : 
	@mkdir -p ${subst src,Debug/src,${shell find src -type d}}

Debug/%.o : %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)

deploy : auto
	@ant

auto :
	scp $(PWD)/auto.dat admin@roborio-5572-frc.local:/home/lvuser/auto.dat 

clean:
	@for dir in src; do find $$dir -name \*.o -exec $(RMCOMMAND) {} \; ; done
	$(RMCOMMAND) bin/*

doc :
	doxygen Doxyfile
	make -C latex
