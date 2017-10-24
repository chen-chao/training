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

test/test_stack.o: test/test_stack.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

bin/test_stack.out: test/test_stack.o $(ODIR)/stack.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm $(ODIR)/*.o

uninstall:
	rm bin/calculator.out
