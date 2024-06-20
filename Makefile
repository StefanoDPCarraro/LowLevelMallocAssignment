CFLAGS = -Wall

PROG = main.exe
FONTES = main.c mymemory.c
OBJETOS = $(FONTES:.c=.o)

all:
	gcc $(CFLAGS) -c $(FONTES)
	gcc $(CFLAGS) -o $(PROG) $(OBJETOS)

clean:
	rm -f $(OBJETOS) $(PROG)
