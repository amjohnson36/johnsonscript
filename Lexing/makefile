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

tests     : scanner
			./scanner test1
			./scanner test2
			./scanner test3
			./scanner test4
			./scanner test5

test1     : scanner 
			./scanner test1

test2     : scanner 
			./scanner test2

test3     : scanner 
			./scanner test3

test4     : scanner 
			./scanner test4

test5     : scanner         # This should fail
			./scanner test5

clean	  :
			rm -f $(OBJS) scanner 
