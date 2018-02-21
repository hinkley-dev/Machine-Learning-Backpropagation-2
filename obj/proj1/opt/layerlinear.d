../obj/proj1/opt/layerlinear.o: layerlinear.cpp layer.h vec.h error.h rand.h matrix.h \
 layerlinear.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c layerlinear.cpp -o ../obj/proj1/opt/layerlinear.o
