// Name: Harrison Walls
// Title: Game of Life
#include "GameOfLife.h"

//Parameterized constructor, creates grid, tempGrid with w,h dimensions, constructs x and y domains.
GameOfLife::GameOfLife(const int w, const int h): width(w), height(h) {
    grid = new bool*[width];
    tempGrid = new bool*[width];
    
    for (size_t i = 0; i < width; ++i) {
        grid[i] = new bool[height];
        tempGrid[i] = new bool[height];
    }
    
    xdomain = new int [3];
    ydomain = new int [3];
    
    srand((unsigned)time(NULL));
};

//Destructor cleans up memory for grid and tempGrid, xDomain and yDomain
GameOfLife::~GameOfLife() {
    return;
}

//Randomly populates the grid with beasties
void GameOfLife::randomInit(const double probability) {      
	for(size_t i = 0; i < width; ++i) {
		for(size_t j = 0; j < height; ++j) {
            double r = (double)rand() / RAND_MAX;
			grid[i][j] = (r < probability);
		}
	}
}

//Updates the grid for one time step
void GameOfLife::iterate() {
}

//Helper function to count nearest neighbors and return this count
int GameOfLife::countNeighbors(const int x, const int y) {
    int i, j;
    int count = 0; // Keeps track of the neighbors
    for(i = x; i <= x; i++)
        for(j = y; j <= y; j++)
            count += grid[i][j]; // increases if the neighbor is alive
    count -= grid[x][y];
    return count;
}

//Determines if grid cell x,y is populated
bool GameOfLife::organismAt(const int x, const int y) {
    return grid[x][y];
}
