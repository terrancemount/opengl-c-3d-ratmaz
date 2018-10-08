/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/
#ifndef _EFFECTS_H
#define _EFFECTS_H


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Ratzilla.h"
#include "MazeBuilder.h"

#define FOG_COLOR_WHITE	  0
#define FOG_COLOR_BLUE	  1
#define FOG_COLOR_YELLOW  2
#define FOG_COLOR_GREEN   3
#define FOG_COLOR_MAGENTA 4
#define FOG_COLOR_RED     5
#define FOG_COLOR_CYAN	  6
#define FOG_COLOR_BLACK   7

GLuint fogActive;
GLuint currentFogColor;

void initEffects();
void enableFog();
void disableFog();
void prevFogState();
void setFogColor(GLuint);
void setFogDensity(GLfloat);
void setFogStartEnd(GLfloat, GLfloat);
void setFogMode(GLenum);







#endif