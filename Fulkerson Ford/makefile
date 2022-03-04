all: compile exec_out

compile:
	gcc -o fulkerson fulkerson-ford.c

exec:
	./fulkerson < fulkerson.in

exec_out:
	./fulkerson < fulkerson.in > fulkerson.out

test:
	./fulkerson	
