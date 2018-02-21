../obj/proj1/opt/supervised.o: supervised.cpp supervised.h matrix.h error.h string.h \
 rand.h vec.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c supervised.cpp -o ../obj/proj1/opt/supervised.o
