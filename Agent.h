/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/


/******************************************
* Check for the header file being defined
******************************************/
#ifndef _AGENT_H
#define _AGENT_H

/*************************************
* Agent included headders
*************************************/
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <GL/glut.h>
#include "MazeBuilder.h"  //needs some constances and varables from Mazebuilder.h
#include "Ratzilla.h"    //needs access to newGame funtion in Ratzilla.h
#include "Texture.h"
#include "Lighting.h"

/*******************************************
* Agent constants
*******************************************/
#define RAT 0
#define FOOD 1 
#define NUM_OF_DIRECTIONS 4 //needs to be a multiple of 4
#define AGENT_HEIGHT 0.2

/*********************************************
* Agent structurs
*********************************************/
typedef struct //keep track of all the stuff going on with an agent (ie mouse)
{
	int type; //mouse or food
	int cellNum; //current cell position in the maze
	int dir;     //current direction of the element
	int isVisible; //whether the agent is visible to the screen
}Agent;

/********************************************
* Agent Gobal Vars
*********************************************/
Agent *agents; //an array of agents to be allocated a run time
int numOfAgents; //the current number of agents in the maze

/**********************************************
* Agent prototypes
***********************************************/
void initAgents();  //setup the array of agents
int moveAgent(int, int); //move the agent around the maze
void showAgent(int);  //make the agent visable on the maze
void hideAgent(int);  //hide the agent on the maze
void drawAllAgents(); //draw all the agents in the agents array
void drawFood(int);  //draw a food graphic on the maze
void drawArrow(int, int); //draw an arrow graphic on the maze
void rotateAgent(int, int);//this rotates the rat in the maze

#endif