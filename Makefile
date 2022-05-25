all:
	gcc -std=c11 -Wall -Wextra -Werror -pedantic digraph.c stack.c main.c -o main.exe

run:
	./main.exe