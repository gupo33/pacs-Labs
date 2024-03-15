CXX      ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -O3 -Wall -I. -Wno-conversion-null -Wno-deprecated-declarations -I../../../../../pacs-examples/Examples/include

#EXEC     = mainMuParserGetPot
EXEC     = mainMuParser
#EXEC     = main
LDFLAGS ?= -L../../../../../pacs-examples/Examples/lib #where the muparser library is found, need to include it
#I should update the LD_LIBRARY_PATH to include the path of libmuparser.so, otherwise it won't run (but it will compile)
#LD_LIBRARY_PATH = $LD_LIBRARY_PATH:../../../../../pacs-examples/Examples/lib
LIBS  ?= -lmuparser

all: $(EXEC)

%.o: %.cpp NewtonSolver.hpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $<

$(EXEC): %: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

clean:
	$(RM) *.o

distclean: clean
	$(RM) *~
