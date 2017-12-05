CC = gcc
CFLAGS = -Wall -lm
DEPS = calc.h
ODIR = obj
_OBJ = main.o getop.o stack.o getch.o variable.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

install: bin/calculator.out

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/calculator.out: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test/test.o: test/test.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/test.out: test/test.o $(ODIR)/stack.o $(ODIR)/getch.o
	$(CC) $(CFLAGS) -o $@ $^

test: bin/test.out
clean:
	rm $(ODIR)/*.o

uninstall:
	rm bin/calculator.out
