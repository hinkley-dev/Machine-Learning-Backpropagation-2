../obj/proj1/dbg/neuralnet.o: neuralnet.cpp neuralnet.h vec.h error.h rand.h matrix.h \
 layer.h layerlinear.h layertanh.h supervised.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c neuralnet.cpp -o ../obj/proj1/dbg/neuralnet.o
