GPP := g++
PPFLAGS := -std=c++11
SRC := CG_hw2.cpp utils.cpp pbm_file.cpp ps_image.cpp geometry_objects.cpp transformations.cpp drawing.cpp
EXE := bin/CG_hw2
.PHONY: cleanall

${EXE} : ${SRC}
	${GPP} ${PPFLAGS} -o $@ $^

cleanall :
	-\rm $(EXE)
	