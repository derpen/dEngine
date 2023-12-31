CXX = g++
CXXFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW

SOURCES = main.cpp ./common/shader.cpp ./common/texture.cpp
OBJECTS = $(SOURCES:.cpp=.o)
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
