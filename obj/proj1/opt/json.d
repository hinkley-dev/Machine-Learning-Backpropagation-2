../obj/proj1/opt/json.o: json.cpp json.h error.h string.h
	g++ -Wall -Werror -Wshadow -pedantic -std=c++11 -O3 -c json.cpp -o ../obj/proj1/opt/json.o
