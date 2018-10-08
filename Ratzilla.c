/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
*  
* CS 385
* Spring 2007
* Homework #3
*********************************************************************/

/*************************************
* Include all headders in the project
**************************************/
#include <GL/glew.h>
#include "Ratzilla.h"
#include "include/ShaderUtils.h"
#include "include/InstallShaders.h"
#include "include/make3DNoiseTexture.h"


/***************************************************/
//globals from Dr Meyers code
GLfloat mortar_color[] = {0.85f, 0.86f, 0.83f};
GLfloat brick_color[] = {1.0f, 0.3f, 0.2f};

GLhandleARB brickShader;
GLhandleARB brickShaderAA;
GLhandleARB skyShader;
GLhandleARB graniteShader;
GLhandleARB marbleShader;
GLhandleARB mandelbrotShader;

GLuint noise3DTexName = 0;

/**************************************************/




/**************************************************
* Displays the Author and Title of the program.
* Then it asks for the number of rows  columns for the
* maze;
****************************************************/
void displayPompt()
{
    puts("*****************");
    puts("* KC Mount      *");
    puts("* CS 351        *");
    puts("* Spring 2007   *");
    puts("* Homework #4   *");
    puts("*****************\n");
    
	//prompt the user for 
    printf("Enter the number of rows in the square maze (2 to 50): ");
    scanf("%i", &numOfRows);
	
	//if maze is too small then set to 2
	if(numOfRows <= 0)
		numOfRows = 1;
	//if maze too big then set to 50
	if(numOfRows > 50)
		numOfRows = 50;

	//set the num of row to equal the num of columns
	numOfColumns = numOfRows;
}

/*****************************************
* Initalize for GLUT and GL to work
*******************************************/
void init()
{
	myCamera.CameraMode = EAGLE_EYE;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //set to use double buffering and RGB color space
	glutInitWindowSize(700, 700);  //set default window size
	glutCreateWindow("Ratzilla 3D");    //set the name of the window
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);  //set the clear color (used in the display callback
	

	clearTransforms();
    srand(time(0)); //seed the random number generator

	//setup callbacks
		
	glutDisplayFunc(display);  //set the display callback
	glutReshapeFunc(reshape);  //set the reshape callback
	glutSpecialFunc(mySpecialKey);    //set the keyboard callback for the arrow keys
	glutKeyboardFunc(myKeyboard);

	//setup menu
	menuSetup(); //setup the menu callback and all the menu elements

}

/****************************************************
* create a new maze (after the maze has been created)
*****************************************************/
void newGame()
{	
	destoryGame(); //destroys all the previous games stuff if there was a previous game
	initMaze();  //initalize the maze in MazeBuilder.c and creates the maze pattern and theMaze display list
	initAgents();  //setup the Agents (ie the rat) in MazeBuilder.c
}

/****************************************************
* Cleans up all the memory allocations 
*****************************************************/
void destoryGame()
{
	if(maze != NULL) //if the maze has already been allocated then free the space
		free(maze); 

	if(agents != NULL) //if the agents has already been allocated then free the space
		free(agents);

	clearTransforms();
}

/*******************************************************
* Menu call back that ether gets a new maze or exits
******************************************************/
void myMenu(int id)
{
	//determine which menu item was pressed
	switch(id)
	{
		case 100: //create a new maze
			newGame(); //have a new game created
			break;
		case 101: //exit program
			exit(0); 
			break;
		case 210:
			setFogMode(GL_EXP);
			break;
		case 211:
			setFogMode(GL_EXP2);
			break;
		case 212:
			setFogMode(GL_LINEAR);
			break;
		case 220:
			setFogColor(FOG_COLOR_WHITE);
			break;
		case 221:
			setFogColor(FOG_COLOR_BLUE);
			break;
		case 222:
			setFogColor(FOG_COLOR_YELLOW);
			break;
		case 223:
			setFogColor(FOG_COLOR_GREEN);
			break;
		case 224:
			setFogColor(FOG_COLOR_MAGENTA);
			break;
		case 225:
			setFogColor(FOG_COLOR_RED);
			break;
		case 226:
			setFogColor(FOG_COLOR_CYAN);
			break;
		case 227:
			setFogColor(FOG_COLOR_BLACK);
			break;
		case 230:
			setFogDensity(0.75);
			break;
		case 231:
			setFogDensity(0.50);
			break;
		case 232:
			setFogDensity(0.35);
			break;
		case 233:
			setFogDensity(0.25);
			break;
		case 200:
			enableFog();
			break;
		case 201:
			disableFog();
			break;
		case 310:
			setTexMode(GL_MODULATE);
			break;
		case 311:
			setTexMode(GL_BLEND);
			break;
		case 312:
			setTexMode(GL_DECAL);
			break;
		case 313:
			setTexMode(GL_REPLACE);
			break;
		case 300:
			enableTex();
			break;
		case 301:
			disableTex();

	}
	glutPostRedisplay(); //post the new game to the screen
}
/****************************************************
* Sets up the menu for options of new maze and quit
****************************************************/
void menuSetup()
{
	GLint texMenu, texMode, fogDen, fogMode, fogColor, fogMenu;

	

	fogMode = glutCreateMenu(myMenu);
	glutAddMenuEntry("GL_EXP", 210);
	glutAddMenuEntry("GL_EXP2", 211);
	glutAddMenuEntry("GL_LINEAR", 212);

	fogColor = glutCreateMenu(myMenu);
	glutAddMenuEntry("White", 220);
	glutAddMenuEntry("Blue", 221);
	glutAddMenuEntry("Yellow", 222);
	glutAddMenuEntry("Green", 223);
	glutAddMenuEntry("Magenta", 224);
	glutAddMenuEntry("Red", 225);
	glutAddMenuEntry("Cyan", 226);
	glutAddMenuEntry("Black", 227);

	fogDen = glutCreateMenu(myMenu);
	glutAddMenuEntry("0.75", 230);
	glutAddMenuEntry("0.50", 231);
	glutAddMenuEntry("0.35", 232);
	glutAddMenuEntry("0.25", 233);
	
	texMode = glutCreateMenu(myMenu);
	glutAddMenuEntry("Modulate", 310);
	glutAddMenuEntry("Blend", 311);
	glutAddMenuEntry("Decal", 312);
	glutAddMenuEntry("Replace", 313);

	texMenu = glutCreateMenu(myMenu);
	glutAddMenuEntry("Enable Textures", 300);
	glutAddMenuEntry("Disable Textures", 301);
	glutAddSubMenu("Texture Mode", texMode); 

	fogMenu = glutCreateMenu(myMenu);
	glutAddMenuEntry("Enable Fog", 200);
	glutAddMenuEntry("Disable Fog", 201);
	glutAddSubMenu("Fog Mode",fogMode);
	glutAddSubMenu("Fog Density",fogDen);
	glutAddSubMenu("Fog Color",fogColor);
	
	glutCreateMenu(myMenu);  // regester the menu callback
	glutAddMenuEntry("New Maze", 100);  //add a New Maze option
	glutAddSubMenu("Texture Menu",texMenu);
	glutAddSubMenu("Fog Menu",fogMenu);
	glutAddMenuEntry("Quit", 101);     //add a Quit option
	glutAttachMenu(GLUT_RIGHT_BUTTON);  //have the right mouse button activate the menu
}


/****************************************************************************************************
* sets the persective to Eagle eye or rat eye (changes the foiv of glPerspective)
*****************************************************************************************************/
void setPerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	

	if(myCamera.CameraMode == EAGLE_EYE)
		gluPerspective(70.0, aspectRatio, CELL_SIZE,  mazeSize);
	else
		gluPerspective(65.0, aspectRatio, CELL_SIZE * .45,  mazeSize);
}

/*****************************************************
* Sets up camera for ether eagle eye or rat eye view
*****************************************************/
void refreshCameraState()
{	
	GLfloat x, y;

	if(myCamera.CameraMode == EAGLE_EYE)
	{
		myCamera.eyeLook[0] = 0.0;		myCamera.eyeLook[1] = 0.0;		myCamera.eyeLook[2] = numOfRows * CELL_SIZE;
		myCamera.centerLook[0] = 0.0;	myCamera.centerLook[1] = 0.0;	myCamera.centerLook[2] = 0.0;
		myCamera.upLook[0] = 0.0;		myCamera.upLook[1] = 1.0;		myCamera.upLook[2] = 0.0;
		setFogStartEnd(numOfRows * CELL_SIZE - CELL_SIZE, numOfRows * CELL_SIZE + CELL_SIZE);
	}
	else //camera mode == rat eye
	{
		setFogStartEnd(CELL_SIZE * 0.6, mazeSize);

		x = (GLfloat)(-numOfColumns * CELL_SIZE / 2.0) + ((agents[RAT].cellNum % numOfRows) * CELL_SIZE) + .5 * CELL_SIZE; 
		
		y = (GLfloat)(numOfRows * CELL_SIZE / 2.0) - ((agents[RAT].cellNum / numOfColumns) * CELL_SIZE) - .5 * CELL_SIZE; 
				
		myCamera.upLook[0] = 0.0;
		myCamera.upLook[1] = 0.0;
		myCamera.upLook[2] = 1.0;

		myCamera.eyeLook[2] = CELL_SIZE * .5;
		myCamera.centerLook[2] = CELL_SIZE * .5;		

		switch(agents[RAT].dir)
		{
			case RIGHT:
				myCamera.eyeLook[0] = x - CELL_SIZE* .7;
				myCamera.eyeLook[1] = y;
				myCamera.centerLook[0] = x + CELL_SIZE;
				myCamera.centerLook[1] = y;
				break;
			
			case UP:
				myCamera.eyeLook[0] = x;
				myCamera.eyeLook[1] = y - CELL_SIZE * .7;
				myCamera.centerLook[0] = x;
				myCamera.centerLook[1] = y + CELL_SIZE;
				break;
			
			case LEFT:
				myCamera.eyeLook[0] = x + CELL_SIZE* .7;
				myCamera.eyeLook[1] = y;
				myCamera.centerLook[0] = x - CELL_SIZE;
				myCamera.centerLook[1] = y;
				break;
			case DOWN:
				myCamera.eyeLook[0] = x;
				myCamera.eyeLook[1] = y + CELL_SIZE * .7;
				myCamera.centerLook[0] = x;
				myCamera.centerLook[1] = y - CELL_SIZE;
				break;
			default:
				printf("bad direction");
				break;
		}
	}
}
/**************************************
* Reshape callback for GLUT
***************************************/
void reshape(GLint w, GLint h)
{   	
	if(h >= w)
		aspectRatio = h/w;
	else
		aspectRatio = w/h;

	glViewport(0, 0, w, h);	
	setPerspective();
}

/**********************************
* Display callback for GLUT
***********************************/
void display(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
	
	refreshCameraState(); //only needed in rat or eagle eye mode 

	glTranslatef(transState.xTrans, transState.yTrans, transState.zTrans); //move the cube

	//point the camera in a new direction
	gluLookAt(myCamera.eyeLook[0],	myCamera.eyeLook[1],		myCamera.eyeLook[2],
			myCamera.centerLook[0],	myCamera.centerLook[1],		myCamera.centerLook[2],
			myCamera.upLook[0],		myCamera.upLook[1],			myCamera.upLook[2]);
	
	setLight(GL_LIGHT0);

	drawMaze();

	drawAllAgents(); //draw the arrow

	glutSwapBuffers();

}

/**********************************
* Special key callback for GLUT
***********************************/
void mySpecialKey(int key, int w, int h)
{
	clearTransforms();
	switch(key)
	{
		case GLUT_KEY_LEFT:  //left arrow pressed 
			rotateAgent(RAT, ROTATE_LEFT);
			break;
		case GLUT_KEY_RIGHT:  //right arrow pressed
			rotateAgent(RAT, ROTATE_RIGHT);
			break;
		case GLUT_KEY_UP:   //up arrow pressed
			moveAgent(RAT, MOVE_FORWARD);
			break;
		case GLUT_KEY_DOWN:  //down arrow pressed
			moveAgent(RAT, MOVE_BACKWARD);
			break;
	}
	glutPostRedisplay();  //once the agent has moved then post a redisplay
}	

//clear all rotation, translation transforms and set x axis to be active.
void clearTransforms()
{
	transState.xTrans = 0.0;
	transState.yTrans = 0.0;
	transState.zTrans = 0.0;
	transState.xRot = 0.0;
	transState.yRot = 0.0;
	transState.zRot = 0.0;	
}


/***********************************************************
* GLUT keyboard call back
*************************************************************/
void myKeyboard(unsigned char key, int x, int y)
{


	switch(key)
	{
		case 27: //escape key
			exit(0); //end program

		//rest the transforms (purge)
		case 'p':
		case 'P':
			clearTransforms(); //rest the cube
			break;
		
		//move view forward (transform)
		case 'w': 
		case 'W':
			transState.zTrans += TRANS_AMT;			
			break;
		
		//move view left (transform)
		case 'a':
		case 'A':
			transState.xTrans += TRANS_AMT;
			break;

		//move view back (transform)
		case 's': 
		case 'S':
			transState.zTrans -= TRANS_AMT;
			break;

		//move view right (transform)
		case 'd':
		case 'D':
			transState.xTrans -= TRANS_AMT;
			break;
		
		//move view up (transform)
		case 'z':
		case 'Z':
			transState.yTrans -= TRANS_AMT;
			break;
		
		//move view down (transform)
		case 'x':
		case 'X':
			transState.yTrans += TRANS_AMT;
			break;

		//toggle view from rat eye to eagle eye
		case 'v':
		case 'V':
			if(myCamera.CameraMode != EAGLE_EYE) //camera set to rat eye or free eye
				myCamera.CameraMode = EAGLE_EYE;
			else //camera mode == eagle eye then set to rat eye
				myCamera.CameraMode = RAT_EYE;
			setPerspective();
			clearTransforms();
			break;
	}
	glutPostRedisplay();
}
/**********************************************
*  Loads the sky shader for the Ratzilla program
*  NOTE: all the code in this function is 
*	from Dr. Meyers
***********************************************/
void loadSkyShader()
{
	int vsLines, fsLines;
	const GLcharARB **vsCode, **fsCode;
	int isValid;
	GLenum err;

	//From Dr. Meyers
	err = glewInit();
	if(GLEW_OK != err)
	{
	  fprintf(stderr,"Error: %s\n", glewGetErrorString(err));
	  fprintf(stderr,"Exiting\n");
	  exit(-1);
	}
	else
	fprintf(stderr,"GLEW successfully initialized\n");

	vsCode = fileToStringArray(&vsLines, "shaders/NoiseVertexShader.glsl");
	fsCode = fileToStringArray(&fsLines, "shaders/SkyFragmentShader.glsl");
	fprintf(stderr,"installing sky shader\n");
	skyShader = installShaders(vsCode, vsLines, fsCode, fsLines);
	fprintf(stderr,"back from installing sky shader\n");
	glValidateProgramARB(skyShader);
	glGetObjectParameterivARB(skyShader, GL_OBJECT_VALIDATE_STATUS_ARB,
				&isValid);
	if(GL_TRUE == isValid)
	{
	  glUseProgramObjectARB(skyShader);
	  printOpenGLError();
	  glUniform1fARB(getUniLoc(skyShader, "Scale"), 0.10);
	  printOpenGLError();
	  CreateNoise3D(&noise3DTexName);
	  fprintf(stderr,"noise3DTexName=%u\n",noise3DTexName);
	  glEnable(GL_TEXTURE_3D);
	  printOpenGLError();
	  glUniform1iARB(getUniLoc(skyShader, "Noise"), 0);
	  printOpenGLError();
	  glUniform3fARB(getUniLoc(skyShader, "SkyColor"),
			  0.0,
			  0.0,
			  0.8);
	  printOpenGLError();
	  glUniform3fARB(getUniLoc(skyShader, "CloudColor"),
			  0.8,
			  0.8,
			  0.8);
	  printOpenGLError();
	  glUniform3fARB(getUniLoc(skyShader, "LightPosition"),
			  0.0f,
			  -5 * mazeSize,
			  0.0f);
	  printOpenGLError();
	}
	else
	{
	  fprintf(stderr,"skyShader does not validate\n");
	  printInfoLog(skyShader);
	  fprintf(stderr,"end of info log for skyShader\n");
	}



}

void setSkyShader(GLuint state)
{
	if(state)
	{
		glEnable(GL_TEXTURE_3D);
		glUseProgramObjectARB(skyShader);
	}
	else
	{
		glDisable(GL_TEXTURE_3D);
		glUseProgramObjectARB(0);
	}
}


/**********************************************
* Main function for the Ratzilla program
***********************************************/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	init();

    displayPompt(); //get the number of rows and columns from the user
	initLighting();
	initTextures();
	initMaze();  
	initAgents();
	initEffects();
	loadSkyShader();
	setSkyShader(0);


	glutMainLoop(); //run the main loop of GLUT
	destoryGame(); //clean up all allocated memory;

	return 0;
}
