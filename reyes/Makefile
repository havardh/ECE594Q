CPP=g++
INC=inc

all: src/*.cpp inc/*.h
	g++ -g -Iinc main.cpp src/*.cpp

gen: all
	./a.out
	open out.bmp
