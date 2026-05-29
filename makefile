CFLAGS = -Wall -Wextra `sdl2-config --libs --cflags`

build: code.c
	gcc $(CFLAGS) -o random-walk code.c && ./random-walk
	rm random-walk
