#sample 'make' build executable file for cpp program
#need to change the following line to your SYSTEMC path
<<<<<<< HEAD
<<<<<<< HEAD
SYSTEMC=C:\dev\systemc-2.3.3\systemc-2.3.3\
=======
SYSTEMC=C:\dev\systemc-2.3.3\
>>>>>>> cebc3ae821e15583a679e11acf8154812a2da0ba
=======
SYSTEMC=C:\dev\systemc-2.3.3\
>>>>>>> cebc3ae821e15583a679e11acf8154812a2da0ba

CC = g++

TARGET = main
INCLUDES = -I. -I$(SYSTEMC)/include
LFLAGS = -L. -L$(SYSTEMC)/lib-linux64 
LIBS = -lsystemc

#This line needs to change to the name of the .cpp file, without the file extension
MAIN = main

SRCS = $(shell ls *.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))


export LD_LIBRARY_PATH := $(SYSTEMC)/lib-linux64
.PHONY: depend clean

all: $(MAIN)
	@echo The program has been successfully compiled

default: $(MAIN)

$(MAIN): $(OBJS)	
	$(CC) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(MAIN) $(OBJS)
	
$(MAIN).o:
	$(CC) $(INCLUDES) $(LFLAGS) $(LIBS) -c $(SRCS)
	
	
clean:
	$(RM) $(MAIN) *.o *~
	
depend: $(SRCS)
	makedepend $(INCLUDES) $^
	
