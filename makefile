CFLAGS = -Wall -Wextra `sdl2-config --libs --cflags`
ants: code.c
	gcc $(CFLAGS) -o random-walk code.c && ./random-walk 
	rm -f random-walk

%:
	gcc $(CFLAGS) -o random-walk code.c && ./random-walk $@
	rm -f random-walk
