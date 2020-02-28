CXXFLAGS = -std=c++11 -O3
LIBS += -lGL -lGLU -lglut -ldrm
.DEFAULT: all
.PHONY: all debug clean
all: dinoshade
debug: CXXFLAGS += -g
dinoshade: dinoshade.cpp
	g++ dinoshade.cpp -o dinoshade $(CXXFLAGS) $(LIBS) $(INC)
clean:
	rm -f *.o
