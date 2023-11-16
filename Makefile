CXX = g++
CXXFLAGS = -std=c++11 -mlibscl -Wall
INCLUDES = -I$(GCCSDK_INSTALL_ENV)/include
LINKS = -L$(GCCSDK_INSTALL_ENV)/lib -lDesk-scl

SRCDIR = src
OBJDIR = build/obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXECUTABLE = !RunImage,ff8

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LINKS) -o build/$(EXECUTABLE) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)