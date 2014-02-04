CC=g++


all: src/*.cpp inc/*.h ../matrix/src/*.cpp ../matrix/inc/*.h
	$(CC) -g -Iinc -I../reyes/inc -I../matrix/inc -I../BasicRayTracer/BasicRayTracer ../BasicRayTracer/BasicRayTracer/*.cpp main.cpp src/*.cpp ../matrix/src/*.cpp -o raytracer -lm -lpthread -I/opt/X11/include -L/opt/local/lib -lm -lpthread -lX11

run: all
	./raytracer ../BasicRayTracer/Scenes/mytest.ascii

open: run
	open out.png
