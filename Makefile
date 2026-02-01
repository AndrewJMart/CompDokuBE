target: main

main: main.o board.o
	g++ objs/main.o objs/board.o -o main

test: test.o board.o
	g++ objs/test.o objs/board.o -o test

main.o: objs
	g++ -c src/main.cpp -lpthread -o objs/main.o

test.o: objs
	g++ -c src/test.cpp -o objs/test.o

board.o: generation.o logical.o utils.o
	g++ -r objs/generation.o objs/logical.o objs/utils.o -o objs/board.o

generation.o: objs
	g++ -c src/board/generation.cpp -o objs/generation.o

logical.o: objs
	g++ -c src/board/logical.cpp -o objs/logical.o

utils.o: objs
	g++ -c src/board/utils.cpp -o objs/utils.o

objs:
	mkdir objs

clean:
	rm -rf objs
	rm -f main
	rm -f test
