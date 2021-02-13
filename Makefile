#sample 'make' build executable file for cpp program
#need to change the following line to your SYSTEMC path
SYSTEMC=C:\dev\systemc-2.3.3\systemc-2.3.3

CC = g++

INCLUDES = -I. -I$(SYSTEMC)/include
LFLAGS = -L. -L$(SYSTEMC)/lib-linux64 
LIBS = -lsystemc

#This line needs to change to the name of the .cpp file, without the file extension
MAIN = main

SRCS = $(MAIN).cpp



OBJS = $(SRCS:.cpp=.o)


export LD_LIBRARY_PATH := $(SYSTEMC)/lib-linux64
.PHONY: depend clean

all: $(MAIN)
	@echo The program has been successfully compiled

default: $(MAIN)

$(MAIN): $(MAIN).o	
	$(CC) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(MAIN) $(OBJS)
	
$(MAIN).o:
	$(CC) $(INCLUDES) $(LFLAGS) $(LIBS) -c $(SRCS)
	
	
clean:
	$(RM) $(MAIN) *.o *~
	
depend: $(SRCS)
	makedepend $(INCLUDES) $^
	