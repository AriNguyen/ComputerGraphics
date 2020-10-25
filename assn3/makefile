GPP := g++
PPFLAGS := -std=c++11
SRC := CG_hw3.cpp 
INCLUDE:= utils.cpp pbm_file.cpp ps_image.cpp geometry_objects.cpp transformations.cpp drawing.cpp time.cpp
EXE := bin/CG_hw2
.PHONY: cleanall

${EXE} : ${SRC} ${INCLUDE}
	${GPP} ${PPFLAGS} -o $@ $^

cleanall :
	-\rm $(EXE)
	