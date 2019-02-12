OBJS = lex.o lexeme.o types.o environment.o parser.o pretty.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

		
all           : pretty

pretty        : $(OBJS) main.c
				gcc $(LOPTS) $(OBJS) main.c -o pp
 
lex.o         : lex.c lex.h
				gcc $(OOPTS) lex.c

lexeme.o      : lexeme.c lexeme.h
				gcc $(OOPTS) lexeme.c

types.o       : types.c types.h
				gcc $(OOPTS) types.c

environment.o : environment.c environment.h
				gcc $(OOPTS) environment.c

parser.o      : parser.c parser.h
				gcc $(OOPTS) parser.c

pretty.o      : pretty.c pretty.h
				gcc $(OOPTS) pretty.c

test1         : pretty
				@echo Original file:
				@cat test1.johns
				@Echo Pretty Printed version of the original:
				@pp test1.johns > test1.pp.1
				@cat test1.pp.1
				@echo Pretty Printed version of the pretty printed version:
				@pp  test1.pp.1 > test1.pp.2
				@cat test1.pp.2
				diff -s -q test1.pp.1 test1.pp.2

test2         : pretty
				@echo Original file:
				@cat test2.johns
				@Echo Pretty Printed version of the original:
				@pp test2.johns > test2.pp.1
				@cat test2.pp.1
				@echo Pretty Printed version of the pretty printed version:
				@pp  test2.pp.1 > test2.pp.2
				@cat test2.pp.2
				diff -s -q test2.pp.1 test2.pp.2

test3         : pretty
				@echo Original file:
				@cat test3.johns
				@Echo Pretty Printed version of the original:
				@pp test3.johns > test3.pp.1
				@cat test3.pp.1
				@echo Pretty Printed version of the pretty printed version:
				@pp  test3.pp.1 > test3.pp.2
				@cat test3.pp.2
				diff -s -q test3.pp.1 test3.pp.2

run           : pretty
				-./pp 

clean	      :
				rm -f $(OBJS) pp
