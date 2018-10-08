/*******************************************************************
* Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #3
*********************************************************************/
#ifndef _AGENT_C
#define _AGENT_C

#include "Agent.h"


//initializes all the agents in the system
void initAgents()
{	
	int numOfAgents = 1;
	int loop; //for the for loop 

	//create space for the array
	agents = (Agent *) ( malloc( numOfAgents * sizeof(Agent))); 

	//loop through the all agents and set the defualt value for the elements in the Agent structure
	for(loop = 0; loop < numOfAgents; loop++)
	{	
		agents[loop].type = RAT;
		agents[loop].cellNum = startCell; //set all agents to the start cell
		agents[loop].dir = RIGHT; //set dir to point right
		agents[loop].isVisible = 1; //set isVisible to true
	}
}


//adds an agent to the "agents" array and sets the parameter in the structure
void addAgent(int typeOfAgent, int cellNum, int dir, int isVisible)
{
	agents = (Agent *) ( realloc( agents, numOfAgents * sizeof(Agent))); //create more space in the array

	//set the elements in the Agent structure to the parameters of the function
	agents[numOfAgents - 1].type = typeOfAgent;
	agents[numOfAgents - 1].cellNum = cellNum;
	agents[numOfAgents - 1].dir = dir;
	agents[numOfAgents - 1].isVisible = isVisible;
}

//rotate the agent
void rotateAgent(int agentNum, int dir)
{
	//check with direction
	if(dir == ROTATE_RIGHT)
	{
		agents[agentNum].dir = agents[agentNum].dir - 1;
		if(agents[agentNum].dir < 0)
			agents[agentNum].dir = NUM_OF_DIRECTIONS - 1;
	}
	else
		agents[agentNum].dir = (agents[agentNum].dir + 1) % NUM_OF_DIRECTIONS;
}

//move the agent in the dir (if connection exits)
int moveAgent(int agentNum, int moveDir)
{	
	GLint prevDir; //used to store the previous direction incase moveDir == MOVE_BACKWARDS

	prevDir = agents[agentNum].dir;
	
	printf("\nRat current dir = %i ", agents[agentNum].dir);  
	
	if(moveDir == MOVE_BACKWARD) //rotate the direction to face backwars
	{
		agents[agentNum].dir = (agents[agentNum].dir + (NUM_OF_DIRECTIONS / 2)) % NUM_OF_DIRECTIONS;
		printf("\nRat back dir = %i", 	agents[agentNum].dir);
	}
	if(maze[agents[agentNum].cellNum].connDir[agents[agentNum].dir] == -1) //if connection does not exist
	{
		agents[agentNum].dir = prevDir; //switch back the direction of the arrow if backwards used
		return 0; //return false : unsuccessful movement
	}

	//else connection exists : set the cellNum of the agent to the connDir in the maze
	agents[agentNum].cellNum = maze[agents[agentNum].cellNum].connDir[agents[agentNum].dir];

	if(moveDir == MOVE_BACKWARD) //rotate the direction to face backwars
		agents[agentNum].dir = prevDir; //switch back the direction of the arrow if backwards used

	if(agents[agentNum].cellNum == endCell)
		newGame();

	return 1; //return true : successful movement
}

//set isVisible for agent to true (will be drawn)
void showAgent(int agentNum)
{
	agents[agentNum].isVisible = 1; //set to true
}

//set isVisible for agent to false (will not be drawn)
void hideAgent(int agentNum)
{
	agents[agentNum].isVisible = 0; //set to false
}

//draws all visible agents in the maze (i.e. mouse)
void drawAllAgents()
{
	//printf("\nRAT cellNum = %i , RAT dir = %i", agents[RAT].cellNum, agents[RAT].dir);
	//draw Mouse
	drawArrow(agents[RAT].cellNum, agents[RAT].dir);
}


//draw an arrow inside a cell at "cellNum" with direction "dir"
void drawArrow(int cellNum, int dir)
{
	

	GLfloat x, y; //start out at the top left of the current cell
	
	//define the shaft at origin with direction right 
	GLfloat vShaft[4][3] = {{ 0.1 * CELL_SIZE,  0.1 * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT}, 
							{-0.3 * CELL_SIZE,  0.1 * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT},
							{-0.3 * CELL_SIZE, -0.1 * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT},
							{ 0.1 * CELL_SIZE, -0.1 * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT}}; 
	
	//define the head at origin with direction right
	GLfloat vHead [3][3] = {{0.1 * CELL_SIZE, 0.2  * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT},
							{0.1 * CELL_SIZE, -0.2 * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT},
							{0.3 * CELL_SIZE, 0.0  * CELL_SIZE, CELL_SIZE * AGENT_HEIGHT}};  

	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor4f(1.0, 1.0, 1.0, 1.0);


	//set the initail x to the top of the current cell 
	x = (GLfloat)(-numOfColumns * CELL_SIZE / 2.0) + ((cellNum % numOfRows) * CELL_SIZE) + .5 * CELL_SIZE;  

	//set the initail y to the left of the current cell
	y = (GLfloat)(numOfRows * CELL_SIZE / 2.0) - ((cellNum / numOfColumns) * CELL_SIZE) - .5 * CELL_SIZE; 

	glTranslatef(x, y, 0.0); //move the mouse model to the correct spot (note with will happen after the rotate)

	//determine which way the arrow is pointing and set the vertices for the shaft and head
	switch(dir)
	{
		case RIGHT:
			//don't need to rotate the arrow
			break;
		case LEFT:
			glRotatef(180.0, 0.0, 0.0, 1.0); //rotate 180 degrees around the z axis to face left
			break;
		case UP:
			glRotatef(90.0, 0.0, 0.0, 1.0); //rotate 90 degrees around the z axis to face up
			break;	 
		case DOWN:
			glRotatef(270.0, 0.0, 0.0, 1.0); //rotate 90 degrees around the z axis to face down
			break;	
		default: //error with the direction
			printf("Error, Incorrect Direction: drawMouse");
			
	}  
	//set mouse pointer to be white
	glColor3f(1.0, 1.0, 1.0);

	//draw shaft
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vShaft[0]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vShaft[1]);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vShaft[2]);
		glTexCoord2f(1.0, 0.0); glVertex3fv(vShaft[3]);
	glEnd();

	//draw head
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0); glVertex3fv(vHead[0]);
		glTexCoord2f(0.5, 1.0); glVertex3fv(vHead[1]);
		glTexCoord2f(0.0, 1.0); glVertex3fv(vHead[2]);
	glEnd();

	prevTexState();
	glEnable(GL_LIGHTING);
		
}

#endif