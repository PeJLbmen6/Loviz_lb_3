#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void DFS(int** G, int numG, int* visited, int s) {
    visited[s] = 1;
    printf("%3d", s);
    for (int i = 0; i < numG; i++) {
        if (G[s][i] == 1 && visited[i] == 0) {
            DFS(G, numG, visited, i);
        }
    }
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int** G;
    int* visited;
    int numG;
    int current;

    srand(time(NULL));

    printf("Номер вершины: ");
    scanf("%d", &numG);

   
    G = (int**)malloc(numG * sizeof(int*));
    visited = (int*)malloc(numG * sizeof(int));

    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
    }

    
    for (int i = 0; i < numG; i++) {
        visited[i] = 0;
    }

    
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            if (i == j) {
                G[i][j] = 0; 
            }
            else {
                G[i][j] = rand() % 2;  
            }
        }
    }

    
    printf("Матрица смежности:\n");
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", G[i][j]);
        }
        printf("\n");
    }

    printf("Input num of vert: ");
    scanf("%d", &current);

    printf("\nPath is: ");
    DFS(G, numG, visited, current);
    printf("\n");

    
    return 0;
}
