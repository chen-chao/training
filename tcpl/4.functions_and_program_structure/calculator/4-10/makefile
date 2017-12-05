CC = gcc
CFLAGS = -ansi -Wall -lm -g
DEPS = 4-10.h
OBJ = bin/4-10.o ../obj/variable.o ../obj/stack.o

install: bin/4-10.out

bin/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/4-10.out: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(ODIR)/*.o

uninstall:
	rm bin/4-10.out
