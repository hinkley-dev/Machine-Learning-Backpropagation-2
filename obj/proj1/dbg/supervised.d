../obj/proj1/dbg/supervised.o: supervised.cpp supervised.h matrix.h error.h string.h \
 rand.h vec.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c supervised.cpp -o ../obj/proj1/dbg/supervised.o
