CC = gcc
CFLAGS = -Wall -ansi
_obj = alloc.o readlines.o sorttext.o
OBJ = $(patsubst %.o, bin/%.o, $(_obj))

bin/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

bin/sorttext: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm bin/*.o

uninstall:
	rm bin/sorttext
