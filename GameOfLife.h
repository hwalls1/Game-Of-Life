
#ifndef GOL_H
#define GOL_H
#pragma once

#include <cstdlib>
#include <ctime>

//Header file for GameOfLife class
class GameOfLife {
private:
	bool** grid;        //grid that is currently displayed
    bool** tempGrid;    //temporary grid for updates - will become
                        //grid for display
    
    int *xdomain;       //to handle neighbors in x - row above,
                        //below, same row - used to handle wrap around
    int *ydomain;       //to handle neighbors in y - column above,
                        //below, same column- used to handle wrap around
    
	int width;          //grid dimensions
	int height;
    int countNeighbors(const int, const int);//helper function to count nearest neighbors
public:
    //Parameterized constructor, creates grid, tempGrid with w,h dimensions, constructs x and y domains.
    GameOfLife(const int w, const int h);
    //Destructor cleans up memory for grid and tempGrid, xDomain and yDomain
	~GameOfLife();
    //Randomly populates the grid with beasties
	void randomInit(const double probability = 0.1);
    //Updates the grid for one time step
	void iterate();
    //Determines if grid cell x,y is populated
    bool organismAt(const int x, const int y);
};
#endif
