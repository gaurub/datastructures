#declaring properties
RM = rm -rf

OBJECTS = linkedlist

OFILES = $(OBJECTS:%=%.o)

CCC = gcc

EXECUTABLE = datastruct

LFLAGS = 

LIBS = 

IFLAGS = -I/Developer/SDKs/MacOSX10.7.sdk/usr/include/ -I./include/

BASEDIR =

COMPILEFLAGS += -Wall -g -std=c99 -DDEBUG

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OFILES)
	@echo
	$(CCC) -o $(EXECUTABLE) $(COMPILEFLAGS) $(OFILES) $(IFLAGS) $(LFLAGS) $(LIBS)

%.o : src/%.c
	$(CCC) $(COMPILEFLAGS) $(IFLAGS) $(CCFLAG) -c $<
	
%c : %.h

clean:
	$(RM) $(OFILES)
	$(RM) $(EXECUTABLE)
