../obj/proj1/dbg/layertanh.o: layertanh.cpp layertanh.h vec.h error.h rand.h matrix.h \
 layer.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c layertanh.cpp -o ../obj/proj1/dbg/layertanh.o
