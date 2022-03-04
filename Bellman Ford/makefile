all: compile exec_out

compile:
	gcc -o bellman bellman-ford.c

exec:
	./bellman < bellman.in

exec_out:
	./bellman < bellman.in > bellman.out

test:
	./bellman	
