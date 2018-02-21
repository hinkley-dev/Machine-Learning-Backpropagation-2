../obj/proj1/opt/layer.o: layer.cpp layer.h vec.h error.h rand.h matrix.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c layer.cpp -o ../obj/proj1/opt/layer.o
