../obj/proj1/dbg/layerlinear.o: layerlinear.cpp layer.h vec.h error.h rand.h matrix.h \
 layerlinear.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c layerlinear.cpp -o ../obj/proj1/dbg/layerlinear.o
