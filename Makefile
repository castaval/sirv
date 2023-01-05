CC=gcc

main: src/main.c
	$(CC) -o bin/main src/main.c src/listen.c src/request.c src/response.c