all: help execute1 execute2

compile: 
	gcc djikstra.c -o djikstra

help: compile
	./djikstra -h

execute1: compile
	./djikstra -f exemplo.txt -i 1 -l 5

execute2: compile
	./djikstra -f exemplo.txt -i 1
