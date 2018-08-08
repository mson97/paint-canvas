paint.out: main.o valid.o canvas.o command.o do.o
	gcc -g -Wall -Werror -o paint.out main.o valid.o canvas.o command.o do.o

main.o: main.c canvas.h command.h
	gcc -g -Wall -Werror -c main.c

valid.o: valid.c valid.h
	gcc -g -Wall -Werror -c valid.c

canvas.o: canvas.c canvas.h
	gcc -g -Wall -Werror -c canvas.c

command.o: command.c command.h valid.h do.h
	gcc -g -Wall -Werror -c command.c

do.o: do.c do.h
	gcc -g -Wall -Werror -c do.c

clean:
	rm -f *.o *.out