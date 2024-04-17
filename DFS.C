#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 10

typedef struct {
    int x, y;
} Cell;

int maze[SIZE][SIZE];

void initializeMaze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            maze[i][j] = 1;
        }
    }
}

bool isValid(Cell cell) {
    return cell.x >= 0 && cell.x < SIZE && cell.y >= 0 && cell.y < SIZE && maze[cell.x][cell.y] == 1;
}

bool isVisited(Cell cell) {
    return maze[cell.x][cell.y] == 0;
}

bool hasUnvisitedNeighbor(Cell cell) {
    Cell neighbors[4] = {{cell.x - 2, cell.y}, {cell.x + 2, cell.y}, {cell.x, cell.y - 2}, {cell.x, cell.y + 2}};
    
    for (int i = 0; i < 4; i++) {
        if (isValid(neighbors[i]) && !isVisited(neighbors[i])) {
            return true;
        }
    }
    
    return false;
}

void removeWall(Cell current, Cell neighbor) {
    int wallX = (current.x + neighbor.x) / 2;
    int wallY = (current.y + neighbor.y) / 2;
    maze[wallX][wallY] = 0;
}

void generateMaze(Cell start) {
    maze[start.x][start.y] = 0;
    
    if (hasUnvisitedNeighbor(start)) {
        int directions[4] = {0, 1, 2, 3};
        for (int i = 0; i < 4; i++) {
            int randomIndex = rand() % 4;
            int temp = directions[randomIndex];
            directions[randomIndex] = directions[i];
            directions[i] = temp;
        }
        
        for (int i = 0; i < 4; i++) {
            Cell neighbor;
            switch (directions[i]) {
                case 0:
                    neighbor.x = start.x - 2;
                    neighbor.y = start.y;
                    break;
                case 1:
                    neighbor.x = start.x + 2;
                    neighbor.y = start.y;
                    break;
                case 2:
                    neighbor.x = start.x;
                    neighbor.y = start.y - 2;
                    break;
                case 3:
                    neighbor.x = start.x;
                    neighbor.y = start.y + 2;
                    break;
            }
            
            if (isValid(neighbor) && !isVisited(neighbor)) {
                removeWall(start, neighbor);
                generateMaze(neighbor);
            }
        }
    }
}

void printMaze() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (maze[i][j] == 0) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL));
    initializeMaze();
    Cell start = {0, 0};
    generateMaze(start);
    printMaze();
    
    return 0;
}
