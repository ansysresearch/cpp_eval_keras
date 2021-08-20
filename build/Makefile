CC = g++
CFLAGS  = -g -Wall -std=c++17 -Ofast
LIBS = -static-libstdc++
DIR2 = ../src/

DIR5 = ../include/
INCLUDES = -I$(DIR5)
DIR4 = ../build/
LFLAGS = -L$(DIR4)

SRCS = $(DIR2)utils.cc $(DIR2)tensor.cc $(DIR2)model.cc $(DIR2)baseLayer.cc $(DIR2)activation.cc $(DIR2)flatten.cc $(DIR2)batchNormalization.cc $(DIR2)conv1d.cc $(DIR2)conv2d.cc $(DIR2)dense.cc $(DIR2)elu.cc $(DIR2)embedding.cc $(DIR2)locally1d.cc $(DIR2)locally2d.cc $(DIR2)lstm.cc $(DIR2)maxPooling2d.cc 

OBJS = $(SRCS:.c=.o)

MAIN = libml.a

.PHONY:	depend

all:	$(MAIN)
		@echo  C++ evaluation library has been compiled


$(MAIN):	$(OBJS)
		ar -r -s $(MAIN) $(OBJS)

.cpp.o:	
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:	
		$(RM) *.o *~ $(MAIN)

depend:	$(SRCS)
		makedepend $(INCLUDES) $^
