CXX		 = g++
CXXFLAGS = -std=c++11 -Ofast
LDFLAGS  =
DEPS	 = main.cpp knn.h knn.cpp point.h point.cpp globals.h globals.cpp
OBJFILES = main.o knn.o point.o globals.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)