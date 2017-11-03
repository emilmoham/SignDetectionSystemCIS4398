PROGS=FrameSender FrameSenderTest

OPENCV_LIBS = `pkg-config opencv --libs`
OPENCV_INCLUDES = `pkg-config opencv --cflags`

LIBS = $(OPENCV_LIBS)
INCLUDES = -I. $(OPENCV_INCLUDES)

all:	$(PROGS)

FrameSender:		Frame.o Master.o main.cpp
	mpiCC -g -o FrameSender -O2 main.cpp Frame.o Master.o $(INCLUDES) $(LIBS)

FrameSenderTest:	Frame.o SHA256.o tests/FrameSendTest.cpp
	mpiCC -g -o FrameSenderTest -O2 Frame.o SHA256.o tests/FrameSendTest.cpp $(INCLUDES) $(LIBS)

Frame.o:		Frame.cpp
	mpiCC -g -c -O2 Frame.cpp $(INCLUDES)

Master.o:		Master.cpp
	mpiCC -g -c -O2 Master.cpp $(INCLUDES)

SHA256.o:		SHA256.c
	gcc -c -O2 SHA256.c
