DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=mergeCatalogs
CC=gcc
CXX=g++
##
# Adjust settings for differnt compilers
#
UsingMinGW=$(shell $(CXX) -v 2>&1 | grep "^Target: mingw" | wc -l)
ifeq ($(UsingMinGW), 1)
CPPFLAGS=-g -std=c++11
LFLAGS=
else
CPPFLAGS=-g -std=c++11
LFLAGS=-pthread
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)
CPPS=$(wildcard *.cpp)
LINK=g++ $(CPPFLAGS)
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

# 
# Targets:
# 

all: $(TARGET) unittest 


$(TARGET): mergeCatalogs.o book.o catalog.o
	$(LINK) $(FLAGS) -o $(TARGET) $^ $(LFLAGS)



clean:
	-/bin/rm -rf *.d *.o $(TARGET) unittest docs

documentation:
	-mkdir docs
	doxygen Doxyfile


unittest: catalog.o book.o testCatalog.o unittest.o
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)


make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
