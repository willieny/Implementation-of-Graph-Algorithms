
#include <stdio.h>

#define A 0
#define B 1
#define C 2
#define MAX_NODES 1000
#define O 1000000000

int n;
int e;
int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) {
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = C;
  return x;
}

int bfs(int start, int target) {
  int u, v;
  for (u = 1; u <=n; u++) {
    color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 1; v <=n; v++) {
      if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == C;
}

int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 1; i <=n; i++) {
    for (j = 1; j <=n; j++) {
      flow[i][j] = 0;
    }
  }

  while (bfs(source, sink)) {
    int increment = O;
    for (u = n; pred[u] >= 1; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n; pred[u] >= 1; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    max_flow += increment;
  }
  return max_flow;
}

int pathfordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 1; i <=n; i++) {
    for (j = 1; j <=n; j++) {
      flow[i][j] = 0;
    }
  }

  while (bfs(source, sink)) {
    int increment = O;
    for (u = n; pred[u] >= 1; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = n; pred[u] >= 1; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    max_flow += increment;
  }
}


int main() {

  int a, b, p;
  int s, t;
  for (int i = 1; i <=n; i++) {
    for (int j = 1; j <=n; j++) {
      capacity[i][j] = 0;
    }
  }

  scanf("%d %d %d %d", &n, &e, &s, &t);
  
  for (int i = 1; i <= e; i++) {
      scanf("%d", &a);
      scanf("%d", &b);
      scanf("%d", &p);
      capacity[a][b] = p;
  }

  printf("Fluxo máximo entre os vértices %d e %d: %d\n", s, t, fordFulkerson(s, t));
}





