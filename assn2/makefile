GPP := g++
PPFLAGS := -std=c11
SRC := CG_hw2.cpp utils.cpp PBMFile.cpp PSImage.cpp GeoObjects.cpp
EXE := CG_hw2
.PHONY: cleanall

${EXE} : ${SRC}
	${GPP} ${PPFLAGS} -o $@ $^

cleanall :
	-\rm $(EXE)
	