/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/

#ifndef _TEXTURE_H  //make sure his is only defined once
#define _TEXTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <tiffio.h>
#include "MazeBuilder.h"

#define TEX_WALL_ONE 0
#define TEX_FLOOR_ONE 1
#define TEX_MOUSE_ONE 2

#define NUM_AVAILABLE_TEXTURES 2

GLuint texActive;

/***********************************
* Texture function prototypes
************************************/
void initTextures();
void setTexture(GLint);
void setTexMode(GLenum);
void enableTex();
void disableTex();
void prevTexState();
void readTiffImage(char*, GLuint);



#endif