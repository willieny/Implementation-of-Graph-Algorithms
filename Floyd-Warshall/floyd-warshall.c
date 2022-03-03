#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INT 10000

int neighborWeight(int A[][3], int m, int v, int u) {
	int i;
	for(i = 0; i < m; i++) {
		if((A[i][0] == v && A[i][1] == u)||(A[i][0] == u && A[i][1] == v))
			return A[i][2];	// se forem vizinhos retorna o peso da aresta
	}
	return -1;
}

void printSolution(int n, int M[n+1][n+1], int m, int v0, int vf, int crescent) {
	int i, j;
	if(v0 == -1 && vf == -1) {
		for(i = 1; i <= n; i++) {
	      	for(j = 1; j <= n; j++) {
	      		if(M[i][j] == MAX_INT){
	      			printf("INF\t");
	      		}
	      		else{
	      			printf("%d\t", M[i][j]);
	      		}
		    }	
		    printf("\n");
	    }
	}
	else if(v0 != -1 && vf == -1) {
		for(i = 1; i <= n; i++) {
			printf("%d:%d ", i, M[v0][i]);
		}
		printf("\n");
	}
	else if(v0 != -1 && vf != -1) {
		printf("%d\n", M[v0][vf]);
	}
}

void floydWarshall(int A[][3], int n, int m, int v0, int vf, int crescent) { // A -> lista de arestas e pesos, n-> n° de vértices, m-> n° de arestas, v0 -> vértice inicial
	int i, j, k, v1, v2;
	int M[n+1][n+1];

	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			if(i != j) {
				M[i][j] = MAX_INT;
			}
			else {
				M[i][j]=0;
			}
		}
	}

	for(i = 0; i < m; i++) {
		v1 = A[i][0];
		v2 = A[i][1];
		M[v1][v2] = A[i][2];
	}

	for(k = 1; k <= n; k++) {
		for(i = 1;i <= n; i++){
			for(j = 1; j <= n; j++){
				if(M[i][j] > M[i][k] + M[k][j]) {
					M[i][j] = M[i][k] + M[k][j];
				}
			}
		}
	}
	
	printSolution(n, M, m, v0, vf, crescent);
} 

void printHelp() {
	printf("### Lista de Comandos ###\n");
	printf("-> 'make help'\n");
	printf("    Mostra o help.\n");
	printf("-> 'make compile'\n");
	printf("    Compila o programa.\n");
	printf("-> 'make execute1'\n");
	printf("    Imprime a matriz das distancias minimas entre cada par de vertices (M[i][j] = menor distancia de i a j).\n");
	printf("-> 'make execute2'\n");
	printf("    Imprime as distancias minimas do vertice 1 ate os demais.\n");
	printf("-> 'make execute3'\n");
	printf("    Imprime a distancia minima do vertice 1 ate o vertice 5.\n");
	printf("-> 'make all'\n");
	printf("    Executa todos os comandos acima.\n");
}

int main(int argc, char *argv[]) {
  	int result;
  	int i, j, n, m, v0 = -1, vf = -1, crescent = 0;
  	char *name_arq;

  	for(i = 0; i < argc; i++) {
    	if(strcmp(argv[i], "-h") == 0) {
    		printHelp();
    		return 0;
    	}
    }
    
    for(i = 0; i < argc; i++) {
    	if(strcmp(argv[i], "-f") == 0) {
    		if(strcmp(argv[i+1], "-s") == 0){
    			crescent = 1;
    			name_arq = argv[i+2];
    		}
    		else {
    			name_arq = argv[i+1];
	    	}
    	}	
    }

    for(i = 0; i < argc; i++) {
    	if(strcmp(argv[i], "-i") == 0) {
    		v0 = atoi(argv[i+1]);
    	}
    }

    for(i = 0; i < argc; i++) {
    	if(strcmp(argv[i], "-l") == 0) {
    		vf = atoi(argv[i+1]);
    	}
    }

    FILE *arq;
	arq = fopen(name_arq, "rt");

	if (arq == NULL)
	{
	    printf("Problemas na abertura do arquivo\n");
	}

	fscanf (arq, "%d%d", &n, &m); 
	int A[m][3];

	for(i = 0; i < m; i++) {
		fscanf (arq, "%d%d%d", &A[i][0], &A[i][1], &A[i][2]);
	}
	
	fclose (arq);

	floydWarshall(A, n, m, v0, vf, crescent);

   return 0;
}
