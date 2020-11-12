CXX := g++
CXXFLAGS := -std=c++11
SRC := CG_hw4.cpp 
INCLUDE:= 
EXE := CG_hw4
.PHONY: cleanall

${EXE} : ${SRC} ${INCLUDE}
	${CXX} -I./helper ${CXXFLAGS} $^ -o $@

cleanall :
	-\rm $(EXE)
	-\rm error
	