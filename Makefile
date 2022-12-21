all:surakarta.cpp
	g++ -Wall -fopenmp -Ofast surakarta.cpp -o surakarta
clean:
	rm surakarta