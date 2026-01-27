

target: main

main: main.o
	g++ main.o -o main

main.o:
	g++ -c src/main.cpp -lpthread


board.o:
	g++ -c src/board/board.cpp

clean:
	rm *.o
