target: main

main: main.o board.o
	g++ main.o board.o -o main

main.o:
	g++ -c src/main.cpp -lpthread

board.o:
	g++ -c src/board/board.cpp

clean:
	rm *.o
