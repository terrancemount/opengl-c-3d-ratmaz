/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #3
*********************************************************************/

/******************************************
* Check for the header file being defined
******************************************/
#ifndef _MazeBuilder_H
#define _MazeBuilder_H

/*************************************
* MazeBuilder included headders
*************************************/
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include "Ratzilla.h"
#include "Texture.h"
#include "Lighting.h"

/************************************
* MazeBuilder constances
************************************/
#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

#define CELL_SIZE 1.0  //defines how much space each cell takes up
#define WALL_SIZE_MULT .05 //multiplier for how much of each cell should be the wall
#define TRANS_AMT (CELL_SIZE * .1)
#define OBJ_HEIGHT (CELL_SIZE * .01 )


/*********************************************
* MazeBuilder structurs
*********************************************/
typedef struct //keeps track of weather a cell in the maze has been visited and what are its connections
{
	int hasVisited; //whether cell has been visited
	int connDir[4]; //the number of the cell it connects to in a directions (UP, DOWN, RIGTH, LEFT)
}MazeCell;

/********************************************
* MazeBuilder Gobal Vars
*********************************************/
MazeCell *maze;  //for an array of MazeCells in a one dimentional array of size "mazeSize"
int mazeSize;   //the size of the maze array (num of cells)
int numOfRows;  //the number of rows in the maze
int numOfColumns;  //the number of columns in the maze
int startCell; //the start cell of the maze
int endCell;  //the end cell of the maze
GLuint theMaze; //a pointer to the maze varable
GLuint theTetrahedron; //pointer to the tetrahedron display list for the start and stop states
int maxCount;  //this is the maxium recurtion count so far

/**********************************************
* MazeBuilder prototypes
***********************************************/
void initMaze(); //create space for the maze
void displayMazeArray();  //display the contents of the maze array strutures as text
void createMazePattern(); //wraper class for setup to creating the maze
void createMazeRecursion(int, int, int, int); //recursively create the maze connections in the maze array
int getCellAtDir(int, int);  //get the cell at the direction specified 
int getLeftCell(int cellNum); //calc the left cell num, if invalid return -1
int getRightCell(int cellNum); //calc the right cell num, if invalid return -1
int getUpCell(int cellNum); //calc the up cell num, if invalid return -1
int getDownCell(int cellNum); //calc the down cell num, if invalid return -1
void drawMaze();  //wrapper class to draw the maze
void drawMazeCell(int); //recursively draw the maze
void drawMazeWall(int);  //draw a single wall using openGL
void polygon(GLfloat *, GLfloat *, GLfloat *, GLfloat *);
void wallCube(void);
#endif

