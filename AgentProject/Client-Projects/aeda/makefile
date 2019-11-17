CXX		 = g++
CXXFLAGS = -std=c++11 -Ofast
LDFLAGS  =
DEPS	 = main.cpp algoritmos.cpp data.h data.cpp GPS.h GPS.cpp menu.h menu.cpp praias.h praias.h servicos.h servicos.cpp ui_utilities.h ui_utilities.cpp utilities.h utilities.cpp
OBJFILES = main.o algoritmos.o data.o GPS.o menu.o praias.o servicos.o ui_utilities.o utilities.o
TARGET	 = main


all: $(TARGET)


$(TARGET): $(OBJFILES) $(DEPS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)


clean:
	rm -f $(OBJFILES) $(TARGET) *~

recompile: makefile
	make clean
	make $(TARGET)