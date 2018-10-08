/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #3
*********************************************************************/
#ifndef _RATZILLA_H  //make sure his is only defined once
#define _RATZILLA_H

/*************************************
* Ratzilla included headders
*************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <GL/glut.h>
#include <time.h>
#include "MazeBuilder.h"
#include "Agent.h"
#include "Texture.h"
#include "Lighting.h"
#include "Effects.h"



/*********************************
* Ratzilla defined constances
*********************************/

#define EAGLE_EYE 0  //view style equals eagle eye (looking over the maze)
#define RAT_EYE   1  //view style equals rat eye  (looking from rat's perspective)
#define FREE_EYE  2  //view style equals free eye (free to move around with a start of rat's perspective)
#define MOVE_FORWARD  0  //rat moves forward
#define MOVE_BACKWARD 1  //rat moves backward
#define ROTATE_LEFT  2  //rat rotates left
#define ROTATE_RIGHT 3  //rat rotate right
#define TRANS_MULT 0.1 //the amount of the cell size is moved each time a transition is wanted
#define ROTATE_AMT 5.0 //the number of degrees to rotate left or right each time a rotation is wanted

/*************************************
* Ratzilla Structs
*************************************/

//stores the camera coordinates for use in the glLookAt function
typedef struct
{
	GLint CameraMode; //0 = eagle eye; 1 = rat eye;
	GLfloat eyeLook[3];     //vertices of the eye coordinates for the glLookAt function
	GLfloat centerLook[3];  //vertices of the center coordinates for the glLookAt function
	GLfloat upLook[3];		//vertices of the up coordinates for the glLookAt function
	
}CameraState;


//Stores the difference in translations form current camera corrdinates (not difference not totoal)
typedef struct{
	GLfloat xTrans;
	GLfloat yTrans;
	GLfloat zTrans;
	GLfloat xRot;
	GLfloat yRot;
	GLfloat zRot;
} Transforms;


/***********************************
* Ratzilla Global
************************************/

CameraState myCamera; //pointer to the stored camera data
Transforms transState; //pointer to the stored transforms difference data
GLfloat aspectRatio;  //stores the aspect ratio for the glPerspective function



/***********************************
* Ratzilla function prototypes
************************************/
void setSkyShader(GLuint state);
void displayPompt(void); //display a prompt to user for the maze size
void init(void);  //initalizes all the glut stuff
void newGame(void);  //create a new Game
void destoryGame(); //cleans up all memory allocations
void myMenu(int); //menu callback handler
void menuSetup(void); //sets up the menu
void myMenu(int); //menu callback
void menuSetup(void); //menu setup (menu items and button registration)
void reshape(int, int); //reshape callback
void display(void); //display callback
void myKey(unsigned char, int, int); //arrow key callback
void clearTransforms();  //clears all the transforms done by wasd keys input
void refreshCameraState(); //rechanges the camera state in ether rat or eagle eye mode (how glLookAt is defined)
void setPerspective(); //sets perspective for ether the rat or eagle eye
void mySpecialKey(int key, int w, int h);
void myKeyboard(unsigned char key, int x, int y);

#endif