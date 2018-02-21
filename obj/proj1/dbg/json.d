../obj/proj1/dbg/json.o: json.cpp json.h error.h string.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -g -D_DEBUG -c json.cpp -o ../obj/proj1/dbg/json.o
