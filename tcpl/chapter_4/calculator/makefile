CC = gcc
CFLAGS = -Wall -c
DEPS = calc.h
ODIR = obj
_OBJ = main.o getop.o stack.o getch.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ $<

bin/calculator.out: $(OBJ)
	$(CC) -Wall -o $@ $^

clean:
	rm $(ODIR)/*.o
