CPP=g++
INC=inc

all: src/*.cpp inc/*.h
	g++ -O3 -Iinc main.cpp src/*.cpp -lm -lpthread -I/opt/X11/include -L/opt/local/lib -lm -lpthread -lX11

gen: all
	./a.out

open: gen
	open output/0.png

