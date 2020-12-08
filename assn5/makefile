CXX := g++
CXXFLAGS := -std=c++17
SRC := CG_hw5.cpp 
INCLUDE:= 
EXE := CG_hw5
.PHONY: cleanall

${EXE} : ${SRC} ${INCLUDE}
	${CXX} -I./../helper ${CXXFLAGS} $^ -o $@

cleanall :
	-\rm $(EXE)
	-\rm error
	