#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "GameOfLife.h"
#include "ConfigFile.h"

#include <iostream>

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

//GLUT-OpenGL program to demonstrate Conway's Game
//of Life. Grid wraps around in width and height.

//The following values are read from "game.config",
//these are default values if no config file is present
GLint FPS = 24;
GLint window_width = 600;
GLint window_height = 600;
GLfloat left = 0.0;
GLfloat right = 1.0;
GLfloat bottom = 0.0;
GLfloat top = 1.0;
GLint game_width = 100;
GLint game_height = 100;

GameOfLife *game;

//Display Callback: Drawing into the frame buffer
void display() {
    //set background color - default is white
	glClear(GL_COLOR_BUFFER_BIT);
	
    //x and y size of each grid cell
    GLfloat xSize = (right - left) / game_width;
	GLfloat ySize = (top - bottom) / game_height;
	
    //Draw a quadrilateral for the grid cell if it is populated
	glBegin(GL_QUADS);
	for (GLint x = 0; x < game_width; ++x) {
		for (GLint y = 0; y < game_height; ++y) {
            
            //set openGL quad color based on organism in grid position
            game->organismAt(x, y)?glColor3f(0,1,0):glColor3f(1,0,0);
            //draw the quad
			glVertex2f(    x*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,    y*ySize+bottom);
			glVertex2f((x+1)*xSize+left,(y+1)*ySize+bottom);
			glVertex2f(    x*xSize+left,(y+1)*ySize+bottom);
		}
	}
	glEnd();
    //use double buffering for smooth animation
	glutSwapBuffers();
}

//Menu Callback: Simple menu attached to right button
//Supports quit option and reset grid option
void control_menu(int id)
{
    //Reset the grid and randomly populate
    if(id ==1) {
        game->~GameOfLife();
        game = new GameOfLife(game_width, game_height);
        game->randomInit();
    }
    //Exit the program
    else if(id == 2) exit(0);
    
}

//Reshape callback: Allows the window to be resized
void reshape(int w, int h) {
	window_width = w;
	window_height = h;

	glViewport(0, 0, window_width, window_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}


//Updates the grid, redisplays the grid, and waits based
//on frames per second
void update(int value) {

    //update for next time step
	game->iterate();

    //post a display event in the event queue
	glutPostRedisplay();
    //wait
	glutTimerFunc(1000 / FPS, update, 0);
}

//Reads configuration file:
//Frames per second
//Window dimensions - width, height
//left, right, bottom, top positions for window
//Grid dimensions - width, height
void readConfiguration(char* file) {
	ConfigFile config(file);
	
	config.readInto(FPS, "fps" );
	
	config.readInto(window_width, "window_width" );
	config.readInto(window_height, "window_height" );
	
	config.readInto(left, "left" );
	config.readInto(right, "right" );
	config.readInto(bottom, "bottom" );
	config.readInto(top, "top" );
	
	config.readInto(game_width, "game_width" );
	config.readInto(game_height, "game_height" );
}

//Checks correctness of configuration input
bool checkConfiguration() {
	if (left > right) {
		std::cout << "Ortographic projection values error: 'left' must be less than 'right'" << std::endl;
		return false;
	}
	if (bottom > top) {
		std::cout << "Ortographic projection values error: 'bottom' must be less than 'top'" << std::endl;
		return false;
	}
	if (window_width <= 0 || window_height <= 0 || game_width <= 0 || game_height <= 0) {
		std::cout << "The window's and game's 'width' and 'height' must be greater than 0" << std::endl;
		return false;
	}
	if (game_width >= window_width || game_height >= window_height) {
		std::cout << "Try reducing the game dimensions or increasing the window size for a better visualization" << std::endl;
	}
	
	return true;
}

int main(int argc, char **argv) {
  	glutInit(&argc, argv);
	//Read and check configuration
	if (argc > 1) {
		readConfiguration(argv[1]);
	}
	
	if (!checkConfiguration()) {
		return 0;
	}
    
    //Window initialization
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Game of Life");
	glClearColor(1,1,1,1);
    
    //Menu initialization
    int c_menu = glutCreateMenu(control_menu);
    glutAddMenuEntry("Reset",1);
    glutAddMenuEntry("Quit",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    //Set up for drawing in window
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
    //Create the game and randomly populate the grid
	game = new GameOfLife(game_width, game_height);
	game->randomInit();
	
    //Enter event loop
	update(0);
	glutMainLoop();
		
  	return 0;
}
