/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/
#ifndef _LIGHTING_H  //make sure his is only defined once
#define _LIGHTING_H


#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "MazeBuilder.h"

//materals
#define MAT_EMERALD 0
#define MAT_BRASS 1
#define MAT_CHROME 2
#define MAT_BLACK_RUBBER 3
#define MAT_RUBY 4
#define MAT_WHITE 5


//specify a materal for an object
typedef struct MateralStruct
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
}MateralStruct;

typedef struct LightStruct
{
	GLfloat position[4];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
}LightStruct;

/***********************************
* Texture function prototypes
************************************/
void initLighting();
void setLight(void);
void setMateral(GLint materialEnum);
void cross(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *result);
void normalize(GLfloat *v);

#endif