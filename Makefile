# Makefile - CS370- HW4
CC=gcc
CXX=g++
FILES=modeltoworld.cc model.h model.cc math.h math.cc driver.h driver.cc
OUT_EXE = modeltoworld

build: $(*.cc)
	$(CXX) -Wall -o $(OUT_EXE) $(FILES)
clean:
	rm -f *.o $(OUT_EXE)
tar:
	tar cvf Meyer.Christian.CS410FA17.A1.tar $(FILES) readme.txt Makefile