CXX=g++
CXXFLAGS=-Wall -MMD
INCLUDEFLAGS=-lglfw -lGL
EXEC=gltest
OBJECTS=src/main.o src/shader.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${INCLUDEFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
