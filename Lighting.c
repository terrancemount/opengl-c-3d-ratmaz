/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/
#include "Lighting.h"

/*******************************************
* Structures for Lighting
********************************************/
//specify material properties
MateralStruct materials[] = //emerald
							 {{0.02, 0.17, 0.02, 0.55,
							   0.08, 0.61, 0.08, 0.55,
							   0.63, 0.73, 0.63, 0.55,
						       0.00, 0.00, 0.00, 0.00,
						       77},
							   //brass
							  {0.33, 0.22, 0.03, 1.00,
							   0.78, 0.57, 0.11, 1.00,
					           0.99, 0.94, 0.81, 1.00,
					           0.00, 0.00, 0.00, 0.00,
					           28},
							   //chrome
							  {0.25, 0.25, 0.25, 1.00,
						       0.40, 0.40, 0.40, 1.00,
						       0.77, 0.77, 0.77, 1.00,
						       0.00, 0.00, 0.00, 0.00,
						       77},
							   //black_rubber
							  {0.02, 0.02, 0.02, 1.00,
							   0.01, 0.01, 0.01, 1.00,
							   0.40, 0.40, 0.40, 1.00,
							   0.00, 0.00, 0.00, 0.00,
							   10},
							   //ruby
							  {0.17, 0.01, 0.01, 0.55,
					           0.61, 0.04, 0.04, 0.55,
					           0.73, 0.63, 0.63, 0.55,
					           0.00, 0.00, 0.00, 0.00,
							   77},
							   //white
							  {1.00, 1.00, 1.00, 1.00,
							   1.00, 0.00, 1.00, 1.00,
							   1.00, 1.00, 1.00, 1.00,
							   0.00, 0.00, 0.00, 0.00,
							   100}};

//specify different light propteries
LightStruct lights =  {{0.00, 0.00, CELL_SIZE * 2.0, 1.00},
					    {0.50, 0.50, 0.50, 0.00},	
					    {1.00, 1.00, 1.00, 1.00},
					    {1.00, 1.00, 1.00, 1.00}};

GLfloat global_ambient[] = {0.5,0.5,0.5,1.0};

/***********************************************************
* Initialize the maze with default lighting
*	Parameters: none
*	Return: none
*	SideEffect: none
***********************************************************/
void initLighting()
{
	glShadeModel(GL_SMOOTH); 
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);//almost always enabled
	setLight(GL_LIGHT0); //set up how the light is to be used
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

}
/***********************************************************
* Setup the different light properites for gl lighting
*	Parameters: lightEnum is the light that is being modified.
*				i.e. GL_LIGHT0, etc.
*	Return: none
*	SideEffect: the state of openGL has changed to the 
*				new light settings
***********************************************************/
void setLight(void)
{		
	glLightfv(GL_LIGHT0, GL_POSITION, lights.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lights.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lights.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lights.specular);
}
/***********************************************************
* Setup the different materal properites for gl primatives
*	Parameters: materialEnum is the enum matching
*		the material in the materials array. 
*		i.e. EMERALD, RUBY, etc.
*	Return: none
*	SideEffect: gl will draw "until changed" with 
*				the new material specifications
***********************************************************/
void setMateral(GLint materialEnum)
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, materials[materialEnum].ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[materialEnum].diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materials[materialEnum].specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, materials[materialEnum].emission);
	glMaterialf(GL_FRONT, GL_SHININESS, materials[materialEnum].shininess);
}
/**********************************************
* Find the normal vector for three given points
*  Parameters: a, b, c are points on a plane to
*	   normal vector
*  Return: the normal vector as a GLfloat pointer
*  SideEffects: none
***********************************************/
void cross(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *result)
{
	result[0] = (b[1]-a[1])*(c[2]-a[2])-(b[2]-a[2])*(c[1]-a[1]);
	result[1] = (b[2]-a[2])*(c[0]-a[0])-(b[0]-a[0])*(c[2]-a[2]);
	result[2] = (b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-c[0]);
	normalize(result);
}
/*******************************************************
* Normalize a vector
*	Parameters: v is the vector to be normalize
*	Return: the normalized vector as a GLfloat pointer
*	SideEffects: none
********************************************************/
void normalize(GLfloat *v)
{
	GLfloat d = 0.0;
	GLint i;

	for(i = 0; i < 3; i++)
		d += pow(v[i], 2.0);

	d = sqrt(d);

	if(d > 0.0)
		for(i = 0; i < 3; i++)
			v[i] /= d;
}