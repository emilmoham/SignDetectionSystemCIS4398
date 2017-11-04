CC = gcc
CXX = g++

all: main.cpp headers/GeneralHeaders.h headers/FrameStructs.h headers/consumer.h
	$(CXX) main.cpp -o test -lpthread

qtest: qTest.cpp headers/GeneralHeaders.h headers/SignDetectionQueue.h
	$(CXX) qTest.cpp -o qTest
