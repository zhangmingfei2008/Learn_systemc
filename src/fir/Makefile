
SYSTEMC_ARCH=linux64
SYSTEMC=$(SYSTEMC_HOME)
LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)
#iNCLUDE DIRECTOTIER
INCLUDE_DIRS = -I. -I $(SYSTEMC)/include/

HEADERS = fir.h tb.h

SOURCES = main.cpp fir.cpp tb.cpp

DEPENDENCIES = \
			   Makefile \
			   $(HEADERS) \
			   $(SOURCES)

LIBS = -lsystemc -lstdc++ -lm

TESTS = main

all : $(TESTS)
		./$(TESTS)
		#@make cmp_result

$(TESTS) : $(DEPENDENCICES)
	gcc -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L $(LIB_DIRS) $(LIBS)

clean :
		rm -f $(TESTS) *.dat
