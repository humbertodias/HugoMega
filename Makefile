CXX_FLAGS := -std=c++17 -Wall $(shell pkg-config --cflags sdl2 SDL2_mixer)
LD_FLAGS := $(shell pkg-config --libs sdl2 SDL2_mixer) -lm
CXX := g++

all: hugomain

hugomain: hugomain.cpp
	$(CXX) hugomain.cpp -o hugomain $(CXX_FLAGS) $(LD_FLAGS)

debug: hugomain.cpp
	$(CXX) hugomain.cpp -o hugomain $(CXX_FLAGS) $(LD_FLAGS) -g

clean:
	rm -f hugomain
