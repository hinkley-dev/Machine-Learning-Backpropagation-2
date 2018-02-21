../obj/proj1/opt/main.o: main.cpp error.h string.h rand.h matrix.h vec.h supervised.h \
 baseline.h layer.h layerlinear.h neuralnet.h layertanh.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c main.cpp -o ../obj/proj1/opt/main.o
