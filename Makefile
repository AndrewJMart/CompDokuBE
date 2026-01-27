target: main

main: main.o board.o
	g++ objs/main.o objs/board.o -o main

main.o: objs
	g++ -c src/main.cpp -lpthread -o objs/main.o

board.o: objs
	g++ -c src/board/board.cpp -o objs/board.o

objs:
	mkdir objs

clean:
	rm -r objs
