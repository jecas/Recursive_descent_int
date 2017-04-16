expression: expression.o lex.yy.o
	gcc -Wall -o $@ $^
lex.yy.o: lex.yy.c tokens.h
	gcc -Wall -c -o $@ $<
lex.yy.c: lexer.l
	flex $<
expression.o: expression.c tokens.h
	gcc -Wall -c -o $@ $<
	
.PHONY: clean
	
clean:
	-rm -f *~ expression *.o lex.yy*