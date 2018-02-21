../obj/proj1/dbg/vec.o: vec.cpp vec.h error.h rand.h matrix.h string.h json.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c vec.cpp -o ../obj/proj1/dbg/vec.o
