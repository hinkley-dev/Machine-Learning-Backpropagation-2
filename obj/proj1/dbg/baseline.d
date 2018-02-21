../obj/proj1/dbg/baseline.o: baseline.cpp baseline.h matrix.h vec.h error.h rand.h \
 supervised.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c baseline.cpp -o ../obj/proj1/dbg/baseline.o
