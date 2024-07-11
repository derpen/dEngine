CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

# # Find all .cpp files in the src directory and .c files in the main directory
# SOURCES_CPP = maintwo.cpp $(wildcard src/*.cpp) 
# SOURCES_C = $(wildcard *.c)
#
# # Combine the lists of sources
# SOURCES = $(SOURCES_CPP) $(SOURCES_C)
#
#SOURCES = maintwo.cpp $(wildcard src/*.cpp) glad.c stb_image.cpp
SOURCES = maintwo.cpp ./src/camera.cpp ./src/shader_s.cpp glad.c stb_image.cpp

# Convert source files to object files
OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS := $(OBJECTS:.c=.o)

EXECUTABLE = dEngine

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS)

run:
	./$(EXECUTABLE)
