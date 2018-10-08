/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/

#include "MazeBuilder.h"

//define the vertices for the cube

GLfloat vertices[][3] = {{-CELL_SIZE / 2.0, -CELL_SIZE * WALL_SIZE_MULT, 0.0},
						{  CELL_SIZE / 2.0, -CELL_SIZE * WALL_SIZE_MULT, 0.0},
						{  CELL_SIZE / 2.0,  CELL_SIZE * WALL_SIZE_MULT, 0.0},
						{ -CELL_SIZE / 2.0,  CELL_SIZE * WALL_SIZE_MULT, 0.0},
						{ -CELL_SIZE / 2.0, -CELL_SIZE * WALL_SIZE_MULT, CELL_SIZE},
						{  CELL_SIZE / 2.0, -CELL_SIZE * WALL_SIZE_MULT, CELL_SIZE}, 
						{  CELL_SIZE / 2.0,  CELL_SIZE * WALL_SIZE_MULT, CELL_SIZE}, 
						{ -CELL_SIZE / 2.0,  CELL_SIZE * WALL_SIZE_MULT, CELL_SIZE}};

//define the indices for each side the cube
GLubyte cubeIndices[24] = {0,3,2,1,
						   2,3,7,6,
						   0,4,7,3,
						   1,2,6,5,
						   4,5,6,7,
						   0,1,5,4};

//used in each cell to draw the floor
GLfloat floorVertices[4][3] = {{-CELL_SIZE/2.0,-CELL_SIZE/2.0, 0.0},
							   { CELL_SIZE/2.0,-CELL_SIZE/2.0, 0.0},
							   { CELL_SIZE/2.0, CELL_SIZE/2.0, 0.0},
							   {-CELL_SIZE/2.0, CELL_SIZE/2.0, 0.0}};

GLfloat wall_diffuse[] = {1.0, 0.5, 1.0, 1.0};
GLfloat wall_ambient[] = {1.0, 0.5, 1.0, 1.0};
GLfloat wall_specular[] = {0.0, 0.0, 0.0, 1.0};

/******************************************************
* Initailize the maze. 
*	Notes: Create space for the maze and initailize maze with 
*		default values. Then calls the create maze pattern
*		function.  
*	Parameters: none
*	Return: none
*	SideEffects: none
********************************************************/
void initMaze()
{
    int i, j;
    
    mazeSize = numOfRows * numOfColumns;
    
    //make space for the array of MazeCells 
    maze = (MazeCell *)malloc(mazeSize * sizeof(MazeCell));
    
	//check for out of memory error.
	if(maze == NULL)
	{
		printf("Out of memory error : maze allocation");
		exit(0);
	}
    //initalize all the cells in the array
    for( i = 0; i < mazeSize; i++)
    {
        //initally the cell has not been visited.
        maze[i].hasVisited = 0; 
        
        //set all connections to -1 (meaning no connection)
        for(j = 0; j < 4; j++)
		{
			maze[i].connDir[j] = -1;
		}
    }	
	createMazePattern();

}
/******************************************************
* Creates a maze pattern (Wrapper function)
*	Notes: Sets the start and end cells for maze then
*		fires off the recurtion from the start cell.
*	Parameters: none
*	Return: none
*	SideEffects: none
********************************************************/
void createMazePattern()
{    
     //set the cell number for the start cell
     startCell = rand() % mazeSize; //should be around middle of the maze

	 maxCount = 0;

     //set the end cell row the same as the start cell
     endCell = rand() % mazeSize; 

	 //make sure the end cell and start cell are different
	 while(endCell == startCell)
		 endCell = rand() % mazeSize;

     //start the recursion with the startCell 
     createMazeRecursion(startCell, -1, LEFT, 1);  
     
}
/******************************************************
* Recursively creates a maze pattern
*	Notes: First it see if the current call has a further
*			path throught the maze then the previous previous
*			call.  Then marks the current cell as visited. Then
*			It finds the next direction to move (randomly).  If
*			it can't go there because that cell has already been 
*			visited it goes to the next counter clock wise direction.
*			Once all four directions have been visited then this
*			function exits.
*	Parameters: none
*	Return: none
*	SideEffects: none
********************************************************/
void createMazeRecursion(int cellNum, int prevCell, int dirFrom, int count)
{
     int dir; //random direction;
     int nextCell; //used for the next possible cell
     int i; //for cycling through each direction
          
	if(count > maxCount)
	{
		maxCount = count;
		endCell = cellNum;
	}

     //set the cell to visited
     maze[cellNum].hasVisited = 1;
     
     //connect the current cell to the previous cell
     maze[cellNum].connDir[(dirFrom + 2) % 4] = prevCell;
     
    //get a random direction
    dir = rand() % 4;
    
    //loop through each possible direction and go to that cell, starting at the random "dir"
    for(i = 0; i < 4; i++) //simple loop to loop 4 times
    {
        //check if the nextCell is valid and the next cell has not been visited
        if(((nextCell = getCellAtDir(cellNum, dir)) > -1 ) && (maze[nextCell].hasVisited == 0))
        {
             maze[cellNum].connDir[dir] = nextCell;         
             createMazeRecursion(nextCell, cellNum, dir, count + 1);
        }
        //increment the direction in a counter-clockwise direction
        dir = (dir + 1) % 4;           
    }
}
/******************************************************
* Finds the cell number in directions (dir)
*	Notes: this function only find will call the associated
*			direction function. i.e. getRightCell(), etc. 
*	Parameters: cellNum is where the function looks from
*					next cell
*				dir is the direction (up, down, left right)
*					to look in.
*	Return: none
*	SideEffects: none
********************************************************/
int getCellAtDir(int cellNum, int dir)
{
    //switch for the direction and get the cell number
    switch(dir)
     {
         case RIGHT: 
              return getRightCell(cellNum); 
         case UP:
              return getUpCell(cellNum);
         case LEFT:
              return getLeftCell(cellNum); 
         case DOWN:
              return getDownCell(cellNum); 
         default: //error with the direction
              printf("Error, Incorrect Direction");
              return -1; //return invalid cell
     }  
}

/******************************************************
* Finds the cell number in the left direction (dir)
*	Parameters: cellNum is where the function looks from
*					next cell
*	Return: none
*	SideEffects: none
********************************************************/
int getLeftCell(int cellNum)
{
    int leftCell;
    
    //set to left of current cell   
    leftCell = cellNum - 1;
    
    //if the left cell is on the same row as the current cell 
    if((leftCell / numOfRows) == (cellNum / numOfRows))
        return leftCell;  

    //else invalid cell number (next to wall)
    return -1;    
}

/******************************************************
* Finds the cell number in the right direction (dir)
*	Parameters: cellNum is where the function looks from
*					next cell
*	Return: none
*	SideEffects: none
********************************************************/
int getRightCell(int cellNum)
{
    int rightCell;
    
    //set to right of current cell   
    rightCell = cellNum + 1;
    
    //if the right cell is on the same row as the current cell 
    if((rightCell / numOfRows) == (cellNum / numOfRows))
        return rightCell;  

    //else invalid cell number (next to wall)
    return -1;    
}

/******************************************************
* Finds the cell number in the up direction (dir)
*	Parameters: cellNum is where the function looks from
*					next cell
*	Return: none
*	SideEffects: none
********************************************************/
int getUpCell(int cellNum)
{
    int upCell;
    
    //find the up cell
    upCell = cellNum - numOfColumns;
    
    //check if valid cell
    if(upCell >= 0) //within bounds of the the array
        return upCell;
        
    return -1; //invalid cell
}

/******************************************************
* Finds the cell number in the down direction (dir)
*	Parameters: cellNum is where the function looks from
*					next cell
*	Return: none
*	SideEffects: none
********************************************************/
int getDownCell(int cellNum)
{
    int downCell;
    
    //find down cell
    downCell = cellNum + numOfColumns;
    
    //check if valid cell
    if(downCell < mazeSize) //within the bounds of the array    
        return downCell;
        
    return -1;  //invalid cell
}
//this is the wraper class that will set off the drawMazeRecursion function
void drawMaze()
{
	int curCell;
	GLfloat xStart, yStart; //the starting position in world corrdinates for the maze (starts in bottom, right corner)

	//start in the top right position
	xStart = -((GLfloat)numOfRows * CELL_SIZE / 2.0) + CELL_SIZE / 2.0;  //find the x start pos 
	yStart = ((GLfloat)numOfColumns * CELL_SIZE / 2.0) - CELL_SIZE / 2.0; //find the y start pos
	
	if(myCamera.CameraMode == RAT_EYE)
	{	
		GLfloat normal[3];
		//GLfloat *a = {0.0, 0.0, 0.0};
		GLfloat p1[3] = {(xStart - CELL_SIZE / 2.0) * 10 , (yStart + CELL_SIZE / 2.0) * 10, CELL_SIZE * 3};
		GLfloat p4[3] = {(xStart - CELL_SIZE / 2.0) * 10, (-yStart - CELL_SIZE / 2.0) * 10, CELL_SIZE * 3};
		GLfloat p3[3] = {(-xStart + CELL_SIZE / 2.0) * 10, (-yStart - CELL_SIZE / 2.0) * 10, CELL_SIZE * 3};
		GLfloat p2[3] = {(-xStart + CELL_SIZE / 2.0) * 10, (yStart + CELL_SIZE / 2.0) * 10, CELL_SIZE * 3};

		cross(p1, p2, p3, normal);

		glNormal3fv(normal);

		setSkyShader(1); //set the shader
		
		glBegin(GL_POLYGON);	  
		
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
			
		glEnd();

		setSkyShader(0); //unset the shader
	}
	
	//setSkyShader(1); //set the shaderv
	glPushMatrix();

	glTranslatef(xStart, yStart, 0.0);

	glPushMatrix(); //store copy of start position
	
	//draw the zero cell
	drawMazeCell(0); 

	//draw the rest of the cells
	for(curCell = 1; curCell < mazeSize; curCell++)
	{
		if(curCell % numOfColumns == 0) //if begining of row
		{
			glPopMatrix(); //go back center of cell zero
			glPushMatrix(); //store another copy of the matrix at zero cell
			glTranslatef(0.0, -(curCell / numOfColumns) * CELL_SIZE, 0.0); //translate to the correct row position
		}
		else
			glTranslatef(CELL_SIZE, 0.0, 0.0); //move to the model view matrix to the next cell

		drawMazeCell(curCell); //draw all the walls in the cell
		
	}

	glPopMatrix(); //get rid of copy after the maze has been drawn
	glPopMatrix();

}

//this function will step all the way throught to the end of the maze then start drawing the lines
void drawMazeCell(int cellNum)
{


	

	//set the floor material 
	setMateral(MAT_RUBY);

	//set the floor texture
	setTexture(TEX_FLOOR_ONE);

	//draw floor 
	polygon(floorVertices[0], floorVertices[1], floorVertices[2], floorVertices[3]); 

	//set the wall material
	setMateral(MAT_EMERALD);

	//set the wall texture
	setTexture(TEX_WALL_ONE);

	//draw walls
	//draw up (always)
	if(maze[cellNum].connDir[UP] == -1) //if does not have a connection
		drawMazeWall(UP);
	
	//draw Right (always)
	if(maze[cellNum].connDir[LEFT] == -1) //if does not have a connection
		drawMazeWall(LEFT); //draw the line
	
	//draw left (only if at end of row)
	if(maze[cellNum].connDir[RIGHT] == -1 && (cellNum % numOfColumns) == numOfColumns - 1) //if not connected and at end of row
		drawMazeWall(RIGHT); //draw the line

	//draw up (only if at last row)
	if(maze[cellNum].connDir[DOWN] == -1 && (cellNum / numOfRows) == numOfRows - 1)
		drawMazeWall(DOWN); //draw the line
}


//draw a maze wall at a direction, this assumes current model view matrix is at the center of the current cell
void drawMazeWall(int dir)
{
     glPushMatrix();
	//find which direction and set the two vertices for the line
	switch(dir)
	{
		case RIGHT:
			glTranslatef(CELL_SIZE / 2.0, 0.0, 0.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);			
			break;
		case UP:
			glTranslatef(0.0, CELL_SIZE / 2.0, 0.0);	
			break;
		case LEFT:
			glTranslatef(-CELL_SIZE / 2.0, 0.0, 0.0);
			glRotatef(90.0, 0.0, 0.0, 1.0);		
			break;
		case DOWN:
			glTranslatef(0.0, -CELL_SIZE / 2.0, 0.0);
			break;
		default:
			printf("Error: incorrect direction");
			exit(0);
	}
	wallCube();
	glPopMatrix();
}

/************************************************
* Draws a polygon with vertices a, b, c, d
*	Note: 
*	Parameters: a, b, c, d are 3D vertices for a
*					rectangular polygon
*	Return: none
*	SideEffect: none
***********************************************/
void polygon(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	GLfloat normal[3];
	cross(a, b, c, normal);
	
	glNormal3fv(normal);

	glBegin(GL_POLYGON);
		//set a
		glTexCoord2f(0.0, 0.0);
		glVertex3fv(a);
		
		//set b
		glTexCoord2f(0.0, 1.0);
		glVertex3fv(b);
		
		//set c
		glTexCoord2f(1.0, 1.0);
		glVertex3fv(c);
		
		//set d
		glTexCoord2f(1.0, 0.0);
		glVertex3fv(d);
	
	glEnd();
}

/************************************************
* Makes calls to polygon for all 6 sides of wall
*	Parameters: none
*	Return: none
*	SideEffect: none
***********************************************/
void wallCube(void)
{
/* map vertices to faces */
	
	polygon(vertices[3], vertices[2], vertices[1], vertices[0]);
	polygon(vertices[2], vertices[3], vertices[7], vertices[6]);
	polygon(vertices[0], vertices[4], vertices[7], vertices[3]);
	polygon(vertices[1], vertices[2], vertices[6], vertices[5]);
	polygon(vertices[4], vertices[5], vertices[6], vertices[7]);
	polygon(vertices[0], vertices[1], vertices[5], vertices[4]);
}
