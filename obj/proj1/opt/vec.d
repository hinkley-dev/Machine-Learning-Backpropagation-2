../obj/proj1/opt/vec.o: vec.cpp vec.h error.h rand.h matrix.h string.h json.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c vec.cpp -o ../obj/proj1/opt/vec.o
