PROGS=FrameSender FrameSenderTest

OPENCV_LIBS = `pkg-config opencv --libs`
OPENSSL_LIBS = `pkg-config libcrypto --libs`

OPENCV_INCLUDES = `pkg-config opencv --cflags`
OPENSSL_INCLUDES = `pkg-config libcrypto --cflags`

LIBS = $(OPENCV_LIBS) $(OPENSSL_LIBS)
INCLUDES = $(OPENCV_INCLUDES) $(OPENSSL_INCLUDES)

all:	$(PROGS)

FrameSender:		Frame.o Master.o main.cpp
	mpiCC -g -o FrameSender -O2 main.cpp Frame.o Master.o $(INCLUDES) $(LIBS)

FrameSenderTest:	Frame.o FrameSendTest.cpp
	mpiCC -g -o FrameSenderTest -O2 Frame.o FrameSendTest.cpp $(INCLUDES) $(LIBS)

Frame.o:		Frame.cpp
	mpiCC -g -c -O2 Frame.cpp $(INCLUDES)

Master.o:		Master.cpp
	mpiCC -g -c -O2 Master.cpp $(INCLUDES)
