#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para memset
#include <limits.h> // Para INT_MAX
#include <stdbool.h> // Para tipo bool

// --- Constantes baseadas em restrições típicas do LeetCode ---
// Network Delay Time
#define MAX_N_NWD 101 // Máximo de nós (1 a 100)
// Min Cost to Connect All Points
#define MAX_POINTS_MCAP 1001 // Máximo de pontos
#define MAX_EDGES_MCAP (MAX_POINTS_MCAP * (MAX_POINTS_MCAP - 1) / 2) // Máximo de arestas possíveis
// Course Schedule
#define MAX_COURSES_CS 2001 // Máximo de cursos
#define MAX_PREREQS_CS 5001 // Máximo de pré-requisitos

// --- Problema 1: Network Delay Time (LeetCode 743) ---

// Função para encontrar o vértice com o menor valor de distância, dentre o conjunto de
// vértices ainda não incluídos na árvore de caminhos mínimos
int caminhoMinimo(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int v = 1; v <= n; v++) { // Nós são de 1 a n
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Algoritmo de Dijkstra para caminho mínimo de fonte única
// Usa uma matriz de adjacência para representar o grafo
int networkDelayTime(int times[][3], int timesSize, int n, int k) {
    int graph[MAX_N_NWD][MAX_N_NWD];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = -1; // -1 indica que não há aresta direta
        }
    }

    for (int i = 0; i < timesSize; i++) {
        graph[times[i][0]][times[i][1]] = times[i][2];
    }

    int dist[MAX_N_NWD];  // Vetor de saída. dist[i] armazenará a menor distância de k até i
    bool sptSet[MAX_N_NWD]; // sptSet[i] será verdadeiro se o vértice i estiver incluído na árvore de caminhos mínimos

    // Inicializa todas as distâncias como INFINITO e sptSet[] como falso
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // A distância do vértice de origem para ele mesmo é sempre 0
    dist[k] = 0;

    // Encontra o caminho mínimo para todos os vértices
    for (int count = 0; count < n - 1; count++) {
        // Escolhe o vértice com menor distância dentre os vértices ainda não processados.
        int u = caminhoMinimo(dist, sptSet, n);

        // Se nenhum vértice pôde ser escolhido (ex: parte desconectada do grafo a partir de k)
        if (u == -1) break;

        // Marca o vértice escolhido como processado
        sptSet[u] = true;

        // Atualiza o valor de dist dos vértices adjacentes ao vértice escolhido.
        for (int v = 1; v <= n; v++) {
            // Atualiza dist[v] apenas se não está em sptSet, existe uma aresta de
            // u para v, e o peso total do caminho de k até v passando por u é
            // menor que o valor atual de dist[v]
            if (!sptSet[v] && graph[u][v] != -1 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Encontra a maior distância entre todos os nós
    int max_delay = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            return -1; // Um nó é inalcançável
        }
        if (dist[i] > max_delay) {
            max_delay = dist[i];
        }
    }
    return max_delay;
}

// --- Problema 2: Min Cost to Connect All Points (LeetCode 1584) ---

typedef struct {
    int u, v, weight;
} Edge_mcap;

typedef struct {
    int parent[MAX_POINTS_MCAP];
    int rank[MAX_POINTS_MCAP]; // Para otimização por rank
} DSU_mcap;

// Operação find do DSU
int findSetMcap(DSU_mcap *dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    // Compressão de caminho
    dsu->parent[i] = findSetMcap(dsu, dsu->parent[i]);
    return dsu->parent[i];
}

// Operação union do DSU (por rank)
void uniteSetsMcap(DSU_mcap *dsu, int a, int b) {
    a = findSetMcap(dsu, a);
    b = findSetMcap(dsu, b);
    if (a != b) {
        if (dsu->rank[a] < dsu->rank[b]) {
            int temp = a; a = b; b = temp; // Troca a e b
        }
        dsu->parent[b] = a;
        if (dsu->rank[a] == dsu->rank[b]) {
            dsu->rank[a]++;
        }
    }
}

// Comparador para qsort
int compareEdgesMcap(const void *a, const void *b) {
    Edge_mcap *edgeA = (Edge_mcap *)a;
    Edge_mcap *edgeB = (Edge_mcap *)b;
    return edgeA->weight - edgeB->weight;
}

// Distância de Manhattan
int distanciaManhattan(int p1[], int p2[]) {
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int minCostConnectPoints(int points[][2], int pointsSize) {
    if (pointsSize <= 1) {
        return 0;
    }

    Edge_mcap edges[MAX_EDGES_MCAP];
    int edge_count = 0;

    // Cria todas as arestas
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            edges[edge_count].u = i;
            edges[edge_count].v = j;
            edges[edge_count].weight = distanciaManhattan(points[i], points[j]);
            edge_count++;
        }
    }

    // Ordena as arestas pelo peso
    qsort(edges, edge_count, sizeof(Edge_mcap), compareEdgesMcap);

    DSU_mcap dsu;
    for (int i = 0; i < pointsSize; i++) {
        dsu.parent[i] = i;
        dsu.rank[i] = 0;
    }

    int mst_cost = 0;
    int edges_in_mst = 0;
    for (int i = 0; i < edge_count; i++) {
        if (findSetMcap(&dsu, edges[i].u) != findSetMcap(&dsu, edges[i].v)) {
            mst_cost += edges[i].weight;
            uniteSetsMcap(&dsu, edges[i].u, edges[i].v);
            edges_in_mst++;
            if (edges_in_mst == pointsSize - 1) {
                break; // MST está completa
            }
        }
    }
    return mst_cost;
}


// --- Problema 3: Course Schedule (LeetCode 207) ---

// Nó da lista de adjacência para Course Schedule
typedef struct CS_No {
    int dest;
    struct CS_No* next;
} CS_No;

// Lista de adjacência
CS_No* adj_cs[MAX_COURSES_CS];
int in_degree_cs[MAX_COURSES_CS];

// Função para adicionar uma aresta à lista de adjacência
void addEdgeCS(int src, int dest) {
    CS_No* novoNo = (CS_No*)malloc(sizeof(CS_No));
    if (!novoNo) {
        perror("Falha ao alocar memória para CS_No");
        exit(EXIT_FAILURE);
    }
    novoNo->dest = dest;
    novoNo->next = adj_cs[src];
    adj_cs[src] = novoNo;
    in_degree_cs[dest]++;
}

// Função para liberar a lista de adjacência
void freeAdjListCS(int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        CS_No* atual = adj_cs[i];
        while (atual != NULL) {
            CS_No* temp = atual;
            atual = atual->next;
            free(temp);
        }
        adj_cs[i] = NULL; // Reseta o ponteiro após liberar
    }
}

bool canFinish(int numCourses, int prerequisitos[][2], int prerequisitosSize) {
    // Inicializa a lista de adjacência e os graus de entrada
    for (int i = 0; i < numCourses; i++) {
        adj_cs[i] = NULL;
        in_degree_cs[i] = 0;
    }

    // Constrói o grafo
    for (int i = 0; i < prerequisitosSize; i++) {
        // prerequisito[1] é pré-requisito de prerequisito[0]
        // Aresta de prerequisito[1] -> prerequisito[0]
        addEdgeCS(prerequisitos[i][1], prerequisitos[i][0]);
    }

    // Algoritmo de Kahn para ordenação topológica
    int queue[MAX_COURSES_CS];
    int front = 0, rear = 0;

    // Adiciona todos os nós com grau de entrada 0 à fila
    for (int i = 0; i < numCourses; i++) {
        if (in_degree_cs[i] == 0) {
            queue[rear++] = i;
        }
    }

    int visited_count = 0;
    while (front < rear) {
        int u = queue[front++];
        visited_count++;

        CS_No* temp = adj_cs[u];
        while (temp != NULL) {
            int v = temp->dest;
            in_degree_cs[v]--;
            if (in_degree_cs[v] == 0) {
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    freeAdjListCS(numCourses); // Limpa a memória alocada para a lista de adjacência

    return visited_count == numCourses;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso:\n");
        printf("  %s nwd <n> <k> <times_flat>\n", argv[0]);
        printf("  %s mcap <points_flat>\n", argv[0]);
        printf("  %s cs <numCourses> <prereqs_flat>\n", argv[0]);
        printf("\nExemplos:\n");
        printf("  %s nwd 4 2 2 1 1 2 3 1 3 4 1\n", argv[0]);
        printf("  %s mcap 0 0 2 2 3 10 5 2 7 0\n", argv[0]);
        printf("  %s cs 2 1 0\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "nwd") == 0) {
        // Network Delay Time
        if (argc < 5) {
            printf("Argumentos insuficientes para nwd\n");
            return 1;
        }
        int n = atoi(argv[2]);
        int k = atoi(argv[3]);
        int timesSize = (argc - 4) / 3;
        int times[timesSize][3];
        int idx = 4;
        for (int i = 0; i < timesSize; i++) {
            for (int j = 0; j < 3; j++) {
                times[i][j] = atoi(argv[idx++]);
            }
        }
        int result = networkDelayTime(times, timesSize, n, k);
        printf("%d\n", result);
    } else if (strcmp(argv[1], "mcap") == 0) {
        // Min Cost to Connect All Points
        if ((argc - 2) % 2 != 0) {
            printf("Quantidade de coordenadas inválida para mcap\n");
            return 1;
        }
        int pointsSize = (argc - 2) / 2;
        int points[pointsSize][2];
        int idx = 2;
        for (int i = 0; i < pointsSize; i++) {
            points[i][0] = atoi(argv[idx++]);
            points[i][1] = atoi(argv[idx++]);
        }
        int result = minCostConnectPoints(points, pointsSize);
        printf("%d\n", result);
    } else if (strcmp(argv[1], "cs") == 0) {
        // Course Schedule
        if (argc < 3) {
            printf("Argumentos insuficientes para cs\n");
            return 1;
        }
        int numCourses = atoi(argv[2]);
        int prereqsSize = (argc - 3) / 2;
        int prereqs[prereqsSize][2];
        int idx = 3;
        for (int i = 0; i < prereqsSize; i++) {
            prereqs[i][0] = atoi(argv[idx++]);
            prereqs[i][1] = atoi(argv[idx++]);
        }
        bool result = canFinish(numCourses, prereqs, prereqsSize);
        printf("%s\n", result ? "true" : "false");
    } else {
        printf("Problema não reconhecido: %s\n", argv[1]);
        return 1;
    }
    return 0;
}