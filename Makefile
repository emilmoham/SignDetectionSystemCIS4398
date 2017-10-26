PROGS=FrameSender FrameSenderTest

OPENCV = `pkg-config opencv --cflags --libs`
OPENSSL = `pkg-config libcrypto --cflags --libs`
LIBS = $(OPENCV) $(OPENSSL)

all:	$(PROGS)

FrameSender:		FrameSender.o main.cpp
	mpiCC -o FrameSender -O3 main.cpp FrameSender.o $(LIBS)

FrameSenderTest:	FrameSender.o FrameSendTest.cpp
	mpiCC -o FrameSenderTest -O3 FrameSender.o FrameSendTest.cpp $(LIBS)

FrameSender.o:		FrameSender.cpp
	mpiCC -c -O3 FrameSender.cpp $(LIBS)
