# AnaliseAlgoritmos-Trabalho2

Trabalho 2 de Análise de Algoritmos: Pesquisa e Resolução de Problemas sobre Grafos

## Descrição

Este projeto implementa soluções em C para três problemas clássicos de grafos, inspirados em questões do LeetCode:

- **Network Delay Time** ([LeetCode 743](https://leetcode.com/problems/network-delay-time/description/))
- **Min Cost to Connect All Points** ([LeetCode 1584](https://leetcode.com/problems/min-cost-to-connect-all-points/description/))
- **Course Schedule** ([LeetCode 207](https://leetcode.com/problems/course-schedule/description/))

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