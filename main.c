#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000  // Máximo número de vértices suportados

// Função para criar e inicializar a matriz de adjacência
void initializeMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Função para adicionar uma aresta à matriz de adjacência
void addEdge(int matrix[MAX_VERTICES][MAX_VERTICES], int src, int dest) {
    matrix[src - 1][dest - 1] = 1;
    matrix[dest - 1][src - 1] = 1;  // Grafo não direcionado
}

// Função auxiliar para DFS
void dfs(int matrix[MAX_VERTICES][MAX_VERTICES], int vertex, bool visited[], int numVertices) {
    visited[vertex] = true;
    for (int i = 0; i < numVertices; i++) {
        if (matrix[vertex][i] == 1 && !visited[i]) {
            dfs(matrix, i, visited, numVertices);
        }
    }
}

// Função auxiliar para contar o número de componentes
int countComponents(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    bool visited[MAX_VERTICES];
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    int componentCount = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            dfs(matrix, i, visited, numVertices);
            componentCount++;
        }
    }
    
    return componentCount;
}

int main() {
    FILE* file = fopen("entrada.txt", "r");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    int N, M;
    fscanf(file, "%d", &N);
    fscanf(file, "%d", &M);

    if (M <= 2 && N > 3) {
        printf("FALTAM %d ESTRADAS\n", N - M - 1);
        fclose(file);
        return 0;
    }
    
    int matrix[MAX_VERTICES][MAX_VERTICES];
    initializeMatrix(matrix, N);

    for (int i = 0; i < M; i++) {
        int D, P;
        fscanf(file, "%d %d", &D, &P);
        addEdge(matrix, D, P);
    }

    fclose(file);

    int components = countComponents(matrix, N);
    
    if (components == 1) {
        printf("PROMESSA CUMPRIDA\n");
    } else {
        printf("FALTAM %d ESTRADAS\n", components - 1);
    }

    return 0;
}
