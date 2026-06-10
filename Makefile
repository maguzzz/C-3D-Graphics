build:
	gcc -Wall -std=c99 src/*.c -lmingw32 -lSDL2main -lSDL2 -o renderer.exe
run:
	./renderer
clean:
	del renderer.exe