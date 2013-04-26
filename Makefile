#declaring properties
RM = rm -rf

BIN_DIR = bin

OBJECTS = arraylist linkedlist test_linkedlist

OFILES = $(OBJECTS:%=%.o)

OFILES_BIN = $(OBJECTS:%=$(BIN_DIR)/%.o)

CCC = gcc

EXECUTABLE = datastruct

LFLAGS = -L./lib

LIBS = -lcunit

IFLAGS = -I/Developer/SDKs/MacOSX10.7.sdk/usr/include/ -I./include/

BASEDIR =

COMPILEFLAGS += -Wall -g -std=c99 -DDEBUG

all : $(EXECUTABLE) $(TEST_EXECUTABLE)

$(EXECUTABLE) : $(OFILES)
	@echo
	$(CCC) -o $(EXECUTABLE) $(COMPILEFLAGS) $(OFILES) $(IFLAGS) $(LFLAGS) $(LIBS)

%.o : %.c
	$(CCC) $(COMPILEFLAGS) $(IFLAGS) $(CCFLAG) -c $< -o $@
	
%c : %.h

clean:
	$(RM) $(OFILES)
	$(RM) $(EXECUTABLE)
