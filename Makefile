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

# # Compiler and flags
# CXX = g++
# CXXFLAGS = -std=c++11 -static -Wall -O2
# TESTFLGS = -std=c++11 -DTEST -static -Wall -O2
# INCLUDES = -I$(GCCSDK_INSTALL_ENV)/include

# # Libraries
# LINKS = -L$(GCCSDK_INSTALL_ENV)/lib -lDesk -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lpng -ltiff -ljpeg -lz -llzma -lwebp -lfreetype -lbz2 -lvorbisfile -logg -lmodplug -lvorbis -lmikmod

# # Directories
# SRCDIR = src
# TESTDIR = test
# OBJDIR = build/obj
# BINDIR = build
# TESTBINDIR = build/test

# # Source and object files
# SRC_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
# TEST_SOURCES = $(wildcard $(TESTDIR)/*.cpp)
# SRC_OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC_SOURCES))
# TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.o,$(TEST_SOURCES))

# # Executable
# EXECUTABLE = $(BINDIR)/RunImage,ff8
# TEST_EXECUTABLE = $(TESTBINDIR)/test_runner,ff8

# # Default rule
# all: $(EXECUTABLE)

# # Link the game executable
# $(EXECUTABLE): $(SRC_OBJECTS)
# 	@mkdir -p $(BINDIR)
# 	$(CXX) $(CXXFLAGS) $(LINKS) -o $@ $^

# # Compile source files into object files
# $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@

# # Compile test files into object files
# $(OBJDIR)/%.o: $(TESTDIR)/%.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) -c $(TESTFLGS) $(INCLUDES) $< -o $@

# # Link the test executable
# test: $(TEST_EXECUTABLE)
# 	@echo "Test executable created: $(TEST_EXECUTABLE)"

# $(TEST_EXECUTABLE): $(TEST_OBJECTS) $(SRC_OBJECTS)
# 	@mkdir -p $(TESTBINDIR)
# 	$(CXX) $(TESTFLGS) $(LINKS) -o $@ $^

# # Compile source files into object files
# $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) -c $(TESTFLGS) $(INCLUDES) $< -o $@

# # Clean up
# clean:
# 	rm -f $(SRC_OBJECTS) $(TEST_OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE)
# 	@echo "Cleaned up."

# # Phony targets
# .PHONY: all test clean
