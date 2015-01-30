#/* 
# * Author: David Vela Tirado
# * Software Developer
# * email:  david.vela.tirado@gmail.com
# * 
# */

PHONY: clean
CFLAGS= -g -Wall -c
all:  libparser.a practica4 practica4lib

practica4: practica4.o  parser.o 
	gcc practica4.o parser.o   -o practica4


practica4lib: practica4.o
	gcc practica4.o -L. -lparser -o practica4lib

	
libparser.a: parser.o 
	ar rv libparser.a parser.o  


practica4.o: practica4.c 
	gcc $(CFLAGS) practica4.c


parser.o: parser.c
	gcc $(CFLAGS) parser.c

clean: 
	-rm -f *.o
	-rm -f practica4 practica4lib
	-rm -f libparser.a
