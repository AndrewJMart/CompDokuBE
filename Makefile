target: main

main: main.o board.o
	g++ objs/main.o objs/board.o -o main

test: test.o board.o
	g++ objs/test.o objs/board.o -o test

main.o: objs
	g++ -c src/main.cpp -lpthread -o objs/main.o

test.o: objs
	g++ -c src/test.cpp -o objs/test.o

board.o: objs
	g++ -c src/board/board.cpp -o objs/board.o

objs:
	mkdir objs

clean:
	rm -r objs
	rm main
	rm test
