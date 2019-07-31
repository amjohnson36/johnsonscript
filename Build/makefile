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
				@echo Displaying error1.johns:
				@cat ../Johns../JohnsFiles/error1.johns

error1x       : johnsonscript
				@echo Executing error1.johns:
				-./johnsonscript ../JohnsFiles/error1.johns

error2        : johnsonscript
				@echo Displaying error2.johns:
				@cat ../JohnsFiles/error2.johns

error2x       : johnsonscript
				@echo Executing error2.johns:
				-./johnsonscript ../JohnsFiles/error2.johns

error3        : johnsonscript
				@echo Displaying error3.johns:
				@cat ../JohnsFiles/error3.johns

error3x       : johnsonscript
				@echo Executing error3.johns:
				-./johnsonscript ../JohnsFiles/error3.johns

error4        : johnsonscript
				@echo Displaying error4.johns:
				@cat ../JohnsFiles/error4.johns

error4x       : johnsonscript
				@echo Executing error4.johns:
				-./johnsonscript ../JohnsFiles/error4.johns

error5        : johnsonscript
				@echo Displaying error5.johns:
				@cat ../JohnsFiles/error5.johns

error5x       : johnsonscript
				@echo Executing error5.johns:
				-./johnsonscript ../JohnsFiles/error5.johns

arrays        : johnsonscript
				@echo Displaying arrays.johns:
				@cat ../JohnsFiles/arrays.johns

arraysx       : johnsonscript
				@echo Executing arrays.johns:
				@johnsonscript ../JohnsFiles/arrays.johns

conditionals  : johnsonscript
				@echo Displaying conditionals.johns:
				@cat ../JohnsFiles/conditionals.johns

conditionalsx : johnsonscript
				@echo Executing conditionals.johns:
				@johnsonscript ../JohnsFiles/conditionals.johns

recursion     : johnsonscript
				@echo Displaying recursion.johns:
				@cat ../JohnsFiles/recursion.johns

recursionx    : johnsonscript
				@echo Executing recursion.johns:
				@johnsonscript ../JohnsFiles/recursion.johns

iteration     : johnsonscript
				@echo Displaying iteration.johns:
				@cat ../JohnsFiles/iteration.johns

iterationx    : johnsonscript
				@echo Executing iteration.johns:
				@johnsonscript ../JohnsFiles/iteration.johns

functions     : johnsonscript
				@echo Displaying functions.johns:
				@cat ../JohnsFiles/functions.johns

functionsx    : johnsonscript
				@echo Executing functions.johns:
				@johnsonscript ../JohnsFiles/functions.johns

lambda        : johnsonscript
				@echo Displaying lambda.johns:
				@cat ../JohnsFiles/lambda.johns

lambdax       : johnsonscript
				@echo Executing lambda.johns:
				@johnsonscript ../JohnsFiles/lambda.johns

objects       : johnsonscript
				@echo Displaying objects.johns:
				@cat ../JohnsFiles/objects.johns

objectsx      : johnsonscript
				@echo Executing objects.johns:
				@johnsonscript ../JohnsFiles/objects.johns

problem       : johnsonscript
				@echo Displaying iAVL.johns:
				@cat ../JohnsFiles/iAVL.johns

problemx      : johnsonscript
				@echo Executing iAVL.johns:
				@johnsonscript ../JohnsFiles/iAVL.johns ../JohnsFiles/commands

clean         :
				rm -f $(OBJS) johnsonscript
