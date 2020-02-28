CXXFLAGS = -std=c++11 -O3
INC = -I/usr/local/opencv3.3-cpu/include
LIBS = -L/usr/local/opencv3.3-cpu/lib
LIBS += -lopencv_core -lopencv_highgui -lopencv_videoio
.DEFAULT: all
.PHONY: all debug clean
all: camera
debug: CXXFLAGS += -g
camera: camera.cpp
	g++ camera.cpp -o camera $(CXXFLAGS) $(LIBS) $(INC)
clean:
	rm -f *.o
