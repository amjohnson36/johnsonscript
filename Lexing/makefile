OBJS = lex.o lexeme.o types.o scanner.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

		
all       : scanner

scanner   : $(OBJS) main.c
			gcc $(LOPTS) $(OBJS) main.c -o scanner
 
lex.o     : lex.c lex.h
			gcc $(OOPTS) lex.c

lexeme.o  : lexeme.c lexeme.h
			gcc $(OOPTS) lexeme.c

types.o   : types.c types.h
			gcc $(OOPTS) types.c

scanner.o : scanner.c scanner.h
			gcc $(OOPTS) scanner.c

run       : scanner
			./scanner test1.johns
			./scanner test2.johns
			./scanner test3.johns
			./scanner test4.johns
			./scanner test5.johns

test1     : scanner 
			./scanner test1.johns

test2     : scanner 
			./scanner test2.johns

test3     : scanner 
			./scanner test3.johns

test4     : scanner 
			./scanner test4.johns

test5     : scanner         # This should fail
			./scanner test5.johns

clean	  :
			rm -f $(OBJS) scanner 
