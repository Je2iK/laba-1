CXX = g++
CXXFLAGS = -Wall -std=c++20 -Isrc/include
SRCDIR = src
OBJDIR = o-files
DATADIR = data
TARGET = program
DBMS_TARGET = dbms

OBJS = $(OBJDIR)/main2.o $(OBJDIR)/brt.o
DBMS_OBJS = $(OBJDIR)/dbms.o $(OBJDIR)/brt.o

all: $(TARGET) $(DBMS_TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(DBMS_TARGET): $(DBMS_OBJS)
	$(CXX) $(CXXFLAGS) -o $(DBMS_TARGET) $(DBMS_OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET) $(DBMS_TARGET)

.PHONY: all clean
