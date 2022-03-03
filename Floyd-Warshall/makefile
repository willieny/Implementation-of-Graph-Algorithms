all: help execute1 execute2 execute3 execute4

compile: 
	gcc floyd-warshall.c -o floyd-warshall

help: compile
	./floyd-warshall -h

execute1: compile
	./floyd-warshall -f exemplo.txt

execute2: compile
	./floyd-warshall -f exemplo.txt -i 1 

execute3: compile
	./floyd-warshall -f exemplo.txt -i 1 -l 5