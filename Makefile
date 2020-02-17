cow: lex.yy.o
	gcc -g lex.yy.o -lfl -o cow

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

lex.yy.c: cow.l
	flex cow.l

clean:
	rm -f a.out cow lex.yy.c *.o output