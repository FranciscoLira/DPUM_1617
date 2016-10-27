CFLAGS=-O2 -Wall 
OBJS=$(patsubst %.c,%.o,$(wildcard *.c))
LIBS=

prot: $(OBJS)
	$(CC) $(CFLAGS) -o exec $(OBJS) $(LIBS) -lm

main:
	$(CC) $(CFLAGS) -o exec main.c

do: prot
	./prot

clean: 
	rm exec *.o 

realclean: 
	rm *.o exec	compl *.out
