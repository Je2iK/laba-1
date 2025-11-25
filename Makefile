CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude
OBJDIR = o-files
TARGET = program

OBJS = $(OBJDIR)/main2.o $(OBJDIR)/brt.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)
