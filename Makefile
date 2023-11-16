CXX = g++
CXXFLAGS = -std=c++11 -mlibscl -Wall
INCLUDES = -I$(GCCSDK_INSTALL_ENV)/include
LINKS = -L$(GCCSDK_INSTALL_ENV)/lib -lDesk-scl

SOURCES = main.cpp Application.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = !RunImage,ff8

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LINKS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
