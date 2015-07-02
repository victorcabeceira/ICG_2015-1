CC=g++
CFLAGS=-g -c -W -Wall -Wextra -std=c++11 `sdl2-config --cflags`
LDLIBS=-lglut -lGL -lGLEW -lassimp `sdl2-config --libs` -lSDL2_image -lglfw3 -lrt -lXrandr -lXinerama -lXi -lXcursor -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=prog
SOURCES=$(wildcard *.cpp)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)

clean:
	$(RM) $(OBJECTS) $(TARGET)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
