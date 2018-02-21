../obj/proj1/opt/layertanh.o: layertanh.cpp layertanh.h vec.h error.h rand.h matrix.h \
 layer.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c layertanh.cpp -o ../obj/proj1/opt/layertanh.o
