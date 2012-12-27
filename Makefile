#declaring properties
RM = rm -rf

BIN_DIR = bin

OBJECTS = linkedlist test_linkedlist

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
	$(CCC) -o $(BIN_DIR)/$(EXECUTABLE) $(COMPILEFLAGS) $(OFILES_BIN) $(IFLAGS) $(LFLAGS) $(LIBS)

%.o : src/%.c
	$(CCC) $(COMPILEFLAGS) $(IFLAGS) $(CCFLAG) -c $< -o $(BIN_DIR)/$@
	
%c : %.h

clean:
	$(RM) $(OFILES_BIN)
	$(RM) $(BIN_DIR)/$(EXECUTABLE)
