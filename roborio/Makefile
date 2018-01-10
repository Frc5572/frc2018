

all : 
	g++ ${shell find . -name '*.cpp'} -o out -std=c++1y

doc :
	doxygen Doxyfile
	make -C latex