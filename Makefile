cow: cow.table.o lex.yy.o
	gcc -g cow.table.o lex.yy.o -lfl -o cow -ly

lex.yy.o: lex.yy.c cow.table.h
	gcc -c lex.yy.c -o lex.yy.o

cow.table.o: cow.table.c
	gcc -c cow.table.c

lex.yy.c: cow.l
	flex cow.l

cow.table.c: cow.y
	yacc -dv cow.y

cow.table.h: cow.y
	echo "cow.tab.h was created at the same time as cow.tab.c."

clean:
	rm -f a.out cow lex.yy.c *.o cow.table.c cow.table.h output