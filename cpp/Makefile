PROGS=FrameSender FrameSenderTest

OPENCV_LIBS = `pkg-config opencv --libs`
OPENCV_INCLUDES = `pkg-config opencv --cflags`

LIBS = $(OPENCV_LIBS)
INCLUDES = -I. -I./sd_common $(OPENCV_INCLUDES)

all:	$(PROGS)

FrameSender:		Frame.o Master.o main.cpp
	mpiCC -g -o FrameSender -O2 main.cpp Frame.o Master.o $(INCLUDES) $(LIBS)

FrameSenderTest:	Frame.o SHA256.o tests/FrameSendTest.cpp
	mpiCC -g -o FrameSenderTest -O2 Frame.o SHA256.o tests/FrameSendTest.cpp $(INCLUDES) $(LIBS)

Frame.o:		sd_common/Frame.cpp
	mpiCC -g -c -O2 sd_common/Frame.cpp $(INCLUDES)

Master.o:		Master.cpp
	mpiCC -g -c -O2 Master.cpp $(INCLUDES)

SHA256.o:		sd_common/SHA256.c
	gcc -c -O2 sd_common/SHA256.c $(INCLUDES)
