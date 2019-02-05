OBJS = lex.o lexeme.o types.o recognizer.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

		
all          : recognizer

recognizer   : $(OBJS) main.c
				gcc $(LOPTS) $(OBJS) main.c -o recognizer
 
lex.o        : lex.c lex.h
				gcc $(OOPTS) lex.c

lexeme.o     : lexeme.c lexeme.h
				gcc $(OOPTS) lexeme.c

types.o      : types.c types.h
				gcc $(OOPTS) types.c

recognizer.o : recognizer.c recognizer.h
				gcc $(OOPTS) recognizer.c

run          : recognizer 
				-./recognizer test1.johns
				-./recognizer test2.johns
				-./recognizer test3.johns
				-./recognizer test4.johns
				-./recognizer test5.johns

test1        : recognizer
				./recognizer test1.johns

test2        : recognizer 
				./recognizer test2.johns

test3        : recognizer 
				./recognizer test3.johns

test4        : recognizer 
				./recognizer test4.johns

test5        : recognizer         # This should fail
				./recognizer test5.johns

clean	     :
				rm -f $(OBJS) recognizer 
