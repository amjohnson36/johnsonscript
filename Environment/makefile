OBJS = lexeme.o types.o environment.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

		
all           : environment

environment   : $(OBJS) main.c
				gcc $(LOPTS) $(OBJS) main.c -o environment
 
#lex.o         : lex.c lex.h
#				gcc $(OOPTS) lex.c

lexeme.o      : lexeme.c lexeme.h
				gcc $(OOPTS) lexeme.c

types.o       : types.c types.h
				gcc $(OOPTS) types.c

environment.o : environment.c environment.h
				gcc $(OOPTS) environment.c

run           : environment
				./environment

clean	      :
				rm -f $(OBJS) environment 
