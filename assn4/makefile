GPP := g++
PPFLAGS := -std=c++11
SRC := CG_hw4.cpp 
INCLUDE:= pbm_file.cpp smf_file.cpp utils.cpp geometry_objects.cpp transformations.cpp drawing.cpp
EXE := CG_hw4
.PHONY: cleanall

${EXE} : ${SRC} ${INCLUDE}
	${GPP} ${PPFLAGS} -o $@ $^

cleanall :
	-\rm $(EXE)
	