# Trabalho 2 de Análise de Algoritmos: Pesquisa e Resolução de Problemas sobre Grafos

**Objetivo:** Explorar problemas clássicos de grafos relacionados a três tópicos fundamentais: Caminho Mínimo, Árvore Geradora Mínima e Ordenação Topológica, aplicando conhecimentos teóricos na resolução prática de problemas encontrados em sites de programação competitiva.

## Descrição

Este projeto implementa soluções em C para três problemas clássicos de grafos, inspirados em questões do LeetCode:

- **Network Delay Time** ([LeetCode 743](https://leetcode.com/problems/network-delay-time/description/))
    - **Algoritmo de Dijkstra**  
        Utilizado para encontrar o menor tempo necessário para que todos os nós de um grafo recebam um sinal a partir de um nó de origem. O algoritmo calcula o caminho mínimo de um vértice para todos os outros em um grafo com pesos positivos.
    
- **Min Cost to Connect All Points** ([LeetCode 1584](https://leetcode.com/problems/min-cost-to-connect-all-points/description/))
    - **Algoritmo de Kruskal (Árvore Geradora Mínima)**  
        Utilizado para encontrar o custo mínimo para conectar todos os pontos em um grafo completo, onde o peso das arestas é a distância de Manhattan entre os pontos. O algoritmo utiliza estrutura de união e busca (DSU/Union-Find) para evitar ciclos.

- **Course Schedule** ([LeetCode 207](https://leetcode.com/problems/course-schedule/description/))
    - **Algoritmo de Kahn (Ordenação Topológica em BFS)**  
        Utilizado para verificar se é possível concluir todos os cursos dados os pré-requisitos, ou seja, se o grafo direcionado é acíclico (DAG). O algoritmo faz uma ordenação topológica utilizando uma fila e o grau de entrada dos vértices.

O código principal está em `main.c` e pode ser compilado e testado facilmente via Makefile.

## Como compilar

Abra o terminal na pasta do projeto e execute:

```
make
```

## Como rodar os testes

Para executar todos os testes de exemplo, use:

```
make test
```

## Como usar manualmente

O programa aceita argumentos de linha de comando para cada problema:

- **Network Delay Time:** `./main nwd <n> <k> <times_flat>`

Exemplo:
```
./main nwd 4 2 2 1 1 2 3 1 3 4 1
```

- **Min Cost to Connect All Points:** `./main mcap <points_flat>`

Exemplo:
```
./main mcap 0 0 2 2 3 10 5 2 7 0
```

- **Course Schedule:** `./main cs <numCourses> <prereqs_flat>`

Exemplo:
```
./main cs 2 1 0
```

## Limpeza

Para remover o executável:

```
make clean
```