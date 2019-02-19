OBJS = lex.o lexeme.o types.o environment.o parser.o eval.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g -std=c99

		
all           : johnsonscript

johnsonscript : $(OBJS) main.c
				gcc $(LOPTS) $(OBJS) tree.c main.c -o johnsonscript
 
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

eval.o        : eval.c eval.h
				gcc $(OOPTS) eval.c

error1        : johnsonscript
				@cat files/error1.johns

error1x       : johnsonscript
				@johnsonscript files/error1.johns

error2        : johnsonscript
				@cat files/error2.johns

error2x       : johnsonscript
				@johnsonscript files/error2.johns

error3        : johnsonscript
				@cat files/error3.johns

error3x       : johnsonscript
				@johnsonscript files/error3.johns

error4        : johnsonscript
				@cat files/error4.johns

error4x       : johnsonscript
				@johnsonscript files/error4.johns

error5        : johnsonscript
				@cat files/error5.johns

error5x       : johnsonscript
				@johnsonscript files/error5.johns

arrays        : johnsonscript
				@cat files/arrays.johns

arraysx       : johnsonscript
				@johnsonscript files/arrays.johns

conditionals  : johnsonscript
				@cat files/conditionals.johns

conditionalsx : johnsonscript
				@johnsonscript files/conditionals.johns

recursion     : johnsonscript
				@cat files/recursion.johns

recursionx    : johnsonscript
				@johnsonscript files/recursion.johns

iteration     : johnsonscript
				@cat files/iteration.johns

iterationx    : johnsonscript
				@johnsonscript files/iteration.johns

functions     : johnsonscript
				@cat files/functions.johns

functionsx    : johnsonscript
				@johnsonscript files/functions.johns


lambda        : johnsonscript
				@cat files/lambda.johns

lambdax       : johnsonscript
				@johnsonscript files/lambda.johns

problem       : johnsonscript
				@cat files/problem.johns

problemx      : johnsonscript
				@johnsonscript files/problem.johns

run           : johnsonscript
				@johnsonscript files/test1.johns

clean         : 
				rm -f $(OBJS) johnsonscript





