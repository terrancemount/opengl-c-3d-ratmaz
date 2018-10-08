/*******************************************************************
 Terrance Mount
* trmount@alaska.edu
* 
* CS 385
* Spring 2007
* Homework #5
*********************************************************************/
#include "Texture.h"

GLuint mazeTextures[NUM_AVAILABLE_TEXTURES];

char *wallOneFileName = "wall.tiff";
char *floorOneFileName = "floor.tiff";
char *mouseOneFileName = "mouse.tiff";

/***********************************************************
* Makes all the needed textures for the maze and enable textures
*	Parameters:none
*	Return: none
*	SideEffect: none
***********************************************************/
void initTextures()
{
	//generate space for all textures
	glGenTextures(NUM_AVAILABLE_TEXTURES, mazeTextures);
	
	//create texture for wall
	readTiffImage(wallOneFileName, mazeTextures[TEX_WALL_ONE]);

	//create texture for floor
	readTiffImage(floorOneFileName, mazeTextures[TEX_FLOOR_ONE]);
	
	//create texture for mouse "Rat" whatever
	//readTiffImage(mouseOneFileName, mazeTextures[TEX_MOUSE_ONE]);
	
	setTexMode(GL_MODULATE);

	enableTex();

}
void setTexMode(GLenum mode)
{
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
}
void enableTex()
{
	glEnable(GL_TEXTURE_2D);
	texActive = 1;
}
void disableTex()
{
	glDisable(GL_TEXTURE_2D);
	texActive = 0;
}
void prevTexState()
{
	if(texActive == 1)
		glEnable(GL_TEXTURE_2D);
	else
		glDisable(GL_TEXTURE_2D);
}

/***********************************************************
* Set how all the textures are applied to primatives.
*	Parameters: texEnum is the texture enum that is to be set
*				i.e. TEX_WALL, TEX_FLOOR, etc
*	Return: none
*	SideEffect: none
***********************************************************/
void setTexture(GLint texEnum)
{
	glBindTexture(GL_TEXTURE_2D, mazeTextures[texEnum]);
}


/***********************************************************
* Reads in a Tiff and makes a 2D texture with it.
*	Parameters: name is the filename of the tiff
				texName is the name of the texture object to
					load the tiff
*	Return: none
*	SideEffect: none
***********************************************************/
void readTiffImage(char *name, GLuint texName)
{
	//stuff needed to open tiff
	TIFFRGBAImage img;
	uint32 *raster;
	size_t npixels;
	TIFF *tif;
	char emsg[1024];
	
	//set the texture to be loaded
	glBindTexture(GL_TEXTURE_2D, texName);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	//set filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//open tiff
	tif = TIFFOpen(name, "r");
	if (tif == NULL)
	{
		fprintf(stderr, "tif == NULL\n");
		exit(1);
	}
	if (TIFFRGBAImageBegin(&img, tif, 0,emsg))
	{
		npixels = img.width*img.height;
		raster = (uint32 *)_TIFFmalloc(npixels*sizeof(uint32));
		if (raster != NULL)
		{
			if (TIFFRGBAImageGet(&img, raster, img.width, img.height) == 0)
			{
				TIFFError(name, emsg);
				exit(1);
			}
		}
		TIFFRGBAImageEnd(&img);
		fprintf(stderr, "Read image %s (%d x %d)\n", name, img.width, img.height);
	}
	else 
	{
		TIFFError(name, emsg);
		exit(1);
	}
	//set tiff
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height,0, GL_RGBA, GL_UNSIGNED_BYTE,raster);
	
	//free memory
	_TIFFfree(raster);

}