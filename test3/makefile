GPP := g++
PPFLAGS := -std=c++11
SRC := CG_hw3.cpp 
INCLUDE:= pbm_file.cpp utils.cpp ps_image.cpp geometry_objects.cpp transformations.cpp drawing.cpp
EXE := CG_hw3
.PHONY: cleanall

${EXE} : ${SRC} ${INCLUDE}
	${GPP} ${PPFLAGS} -o $@ $^

cleanall :
	-\rm $(EXE)
	