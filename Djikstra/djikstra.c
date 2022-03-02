#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INT 10000

typedef struct node {
	int item;
	int dist;
	int prev;
	struct node *next;	
} node;

typedef struct priority_queue {
	int current_size;
	node *head;
} priority_queue;

node* create_node(int i) {
	node *new_nd = (node*)malloc(sizeof(node));
	new_nd->item = i;
	new_nd->dist = MAX_INT;
	new_nd->prev = -1;
	new_nd->next = NULL;
}

priority_queue* create_queue()
{
	priority_queue *new_queue = (priority_queue*) malloc(sizeof(priority_queue));
	new_queue->current_size = 0;
	new_queue->head = 0;
	return new_queue;
}

int is_empty(priority_queue *pq) {
	if(pq->current_size == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void enqueue(priority_queue *pq, int i, int p)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = i;
	new_node->dist = p;
	if ((is_empty(pq)) || (p <= pq->head->dist)) {
		new_node->next = pq->head;
		pq->head = new_node;
	} 
	else {
		node *current = pq->head;
		while((current->next != NULL) && (current->next->dist <= p)) {
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
	pq->current_size += 1;
}

node* dequeue(priority_queue *pq)
{
	if (is_empty(pq)) {
		printf("Priority Queue underflow");
		return NULL;
	} 
	else {
		node *node = pq->head;
		pq->head = pq->head->next;
		node->next = NULL;
		pq->current_size -= 1;
		return node;
	}
}

void updatePriority(priority_queue *pq, int i, int p) {
	if(pq->current_size == 1) {
		pq->head->dist = p;
	}
	else if(pq->current_size > 1) {
		node *prev = pq->head;
		node *current = pq->head->next;
		while((current->next != NULL) && (current->item != i)) {
			prev = prev->next;
			current = current->next;
		}
		if(current->item == i) {
			prev->next = current->next;
			current->next = NULL;
			current->dist = p;
			if (p <= pq->head->dist) {
				current->next = pq->head;
				pq->head = current;
			} 
			else {
				node *aux = pq->head;
				while((aux->next != NULL) && (aux->next->dist <= p)) {
					aux = aux->next;
				}
				current->next = aux->next;
				aux->next = current;
			}
		}
	}	
}

void printQueue(priority_queue *pq) {
	node *aux = pq->head;
	printf("fila: ");
	while(aux->next != NULL) {
		printf("%d:%d, ", aux->item, aux->dist);
		aux = aux->next;
	}
	printf("%d:%d, ", aux->item, aux->dist);
	printf("\n");
}

int neighborWeight(int A[][3], int m, int v, int u) {
	int i;
	for(i = 0; i < m; i++) {
		if((A[i][0] == v && A[i][1] == u)||(A[i][0] == u && A[i][1] == v))
			return A[i][2];	// se forem vizinhos retorna o peso da aresta
	}
	return -1;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
void bubbleSort(int arr[], int v[], int n)
{
   int i, j;
   int swapped;
   for (i = 1; i < n-1; i++)
   {
     swapped = 0;
     for (j = 1; j < n-i; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swap(&v[j], &v[j+1]);
           swapped = 1;
        }
     }
     if (swapped == 0)
        break;
   }
}

void printSolution(int dist[], int n, int m, int v0, int vf, int crescent) {
	if(vf != -1) {
		printf("%d\n", dist[vf]);
	}
	else if(crescent == 1) {
		int v[n+1];
		for(int i = 1; i <= n; i++) {
			v[i] = i;
		}
		bubbleSort(dist, v, n+1);
		for(int i = 1; i <= n; i++) {
			printf("%d:%d ", v[i], dist[i]);
		}
		printf("\n");
	}
	else {
		for(int i = 1; i <= n; i++) {
			printf("%d:%d ", i, dist[i]);
		}
		printf("\n");
	}
}

void dijkstra(int A[][3], int n, int m, int v0, int vf, int crescent) { // A -> lista de arestas e pesos, n-> n° de vértices, m-> n° de arestas, v0 -> vértice inicial
	int i, w;
	int visited[n+1], dist[n+1], prev[n+1]; 

	priority_queue *pq = create_queue(); // fila de prioridade

	for(i = 1; i <= n; i++) {
		if(i != v0) {
			enqueue(pq, i, MAX_INT);
			dist[i] = MAX_INT;
		}
		visited[i] = 0; // marca como não visitado
		prev[i] = -1;
	}
	enqueue(pq, v0, 0);
	dist[v0] = 0;

	while(pq->current_size > 0) {
		node *u = dequeue(pq);
		visited[u->item] = 1;	// marca como visitado
		for(i = 1; i <= n; i++) {
			w = neighborWeight(A, m, u->item, i);
			if(w != -1 && visited[i] == 0) {
				if(dist[i] > dist[u->item] + w){
					dist[i] = dist[u->item] + w;
					prev[i] = u->item;
					updatePriority(pq, i, dist[u->item] + w);
				}

			}
		}
	}
	printSolution(dist, n, m, v0, vf, crescent);
} 

void printHelp() {
	printf("### Lista de Comandos ###\n");
	printf("-> 'make help'\n");
	printf("   Mostra o help.\n");
	printf("-> 'make compile'\n");
	printf("   Compila o programa.\n");
	printf("-> 'make execute1'\n");
	printf("   Calcula a distância mínima do vértice 1 até o vértice 5.\n");
	printf("-> 'make execute2'\n");
	printf("   Calcula a distância mínima do vértice 1 até os demais.\n");
	printf("-> 'make execute3'\n");
	printf("   Calcula a distância mínima do vértice 1 até os demais e imprime em ordem crescente.\n");
	printf("-> 'make all'\n");
	printf("   Executa todos os comandos acima.\n");
	printf("-> './djikstra -f <arquivo> -i <v0> -l <vf>'\n");
	printf("   Calcula a distância mínima do vértice v0 até o vértice vf.\n");
	printf("-> './djikstra -f <arquivo> -i <v0>'\n");
	printf("   Calcula a distância mínima do vértice v0 até os demais.\n");
	printf("-> './djikstra -f -s <arquivo> -i <v0>'\n");
	printf("   Calcula a distância mínima do vértice v0 até os demais e imprime em ordem crescente.\n");
}

int main(int argc, char *argv[]) {
  	//char *result;
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

	dijkstra(A, n, m, v0, vf, crescent);

   return 0;
}
