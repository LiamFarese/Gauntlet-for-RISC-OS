CXX = g++
CXXFLAGS = -std=c++11 -static -Wall -O2
INCLUDES = -I$(GCCSDK_INSTALL_ENV)/include
LINKS = -L$(GCCSDK_INSTALL_ENV)/lib -lDesk -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lpng -ltiff -ljpeg -lz -llzma -lwebp -lfreetype -lbz2 -lvorbisfile -logg -lmodplug -lvorbis -lmikmod

SRCDIR = src
OBJDIR = build/obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXECUTABLE = build/RunImage,ff8

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LINKS) -o $(EXECUTABLE) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)