# Teoria dos Grafos - Implementação

## Alunas
* Pâmela Medeiros dos Santos
* Willieny Barbosa de Magalhães

## Algoritmo de Djikstra
**Entrada:** Vértice inicial, vértice final (opcional), grafo não direcionado em arquivo de texto no seguinte formato, sendo 'n' o número de vértices, 'm' o número de arestas e 'u v w' uma aresta entre os vértices 'u' e 'v' com peso 'w':
````
n m
u v w
u v w
u v w
...
````
**Saída:** Lista de distâncias mínimas entre o vértice inicial e os demais no seguinte formato, sendo 'i' o vértice e 'd' a distância mínima até ele a partir do vértice inicial:
````
i:d i:d i:d ...
````
Caso receba também o vértice final, a saída será apenas a distância mínima 'd' entre o vértice inicial e o final.

**Execução:** Para compilar o programa e executar alguns exemplos, execute o comando ```` make all ```` no diretório 'Djikstra'.

## Algoritmo de Floyd-Warshall
**Entrada:** Vértice inicial (opcional), vértice final (opcional), grafo direcionado em arquivo de texto no seguinte formato, sendo 'n' o número de vértices, 'm' o número de arestas e 'u v w' uma aresta que parte do vértice 'u' a 'v' com peso 'w':
````
n m
u v w
u v w
u v w
...
````
**Saída:** Matriz nxn das distâncias mínimas entre cada par de vértices, onde 'M[i][j]' é a menor distância partindo do vértice 'i' até o vértice 'j' (essa distância será 'INF', caso não exista um caminho que parte de 'i' até 'j'):  
````
M[i][j]    M[i][j]    M[i][j]
M[i][j]    M[i][j]    M[i][j]
M[i][j]    M[i][j]    M[i][j]
...
````
Caso seja dado um vértice inicial, a saída será a lista de distâncias mínimas entre o vértice inicial e os demais no seguinte formato, sendo 'i' o vértice e 'd' a distância mínima até ele a partir do vértice inicial:
````
i:d i:d i:d ...
````
Caso receba também o vértice final, a saída será apenas a distância mínima 'd' entre o vértice inicial e o final.

**Execução:** Para compilar o programa e executar alguns exemplos, execute o comando ```` make all ```` no diretório 'Floyd-Warshall'.
