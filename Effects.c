#include "Effects.h"

#define FOG_COLOR_WHITE	  0
#define FOG_COLOR_BLUE	  1
#define FOG_COLOR_YELLOW  2
#define FOG_COLOR_GREEN   3
#define FOG_COLOR_MAGENTA 4
#define FOG_COLOR_RED     5
#define FOG_COLOR_CYAN	  6
#define FOG_COLOR_BLACK   7


GLfloat fogColor[][4] = {{1.0, 1.0, 1.0, 1.0}, //white
						 {0.0, 0.0, 1.0, 1.0}, //blue
						 {1.0, 1.0, 0.0, 1.0}, //yellow
						 {0.0, 1.0, 0.0, 1.0}, //green
						 {1.0, 0.0, 1.0, 1.0}, //magenta
						 {1.0, 0.0, 0.0, 1.0}, //red
						 {0.0, 1.0, 1.0, 1.0}, //cyan
						 {0.0, 0.0, 0.0, 1.0}};//black


void initEffects()
{
	//set up fog
	currentFogColor = FOG_COLOR_WHITE;
	glFogi(GL_FOG_MODE, GL_EXP);
	setFogColor(currentFogColor);
	glFogf(GL_FOG_DENSITY, 0.10);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	disableFog();
	
}
void enableFog()
{
	fogActive = 1;
	glEnable(GL_FOG);
	glClearColor(fogColor[currentFogColor][0], fogColor[currentFogColor][1],
		fogColor[currentFogColor][2], fogColor[currentFogColor][3]); 

}
void disableFog()
{
	fogActive = 0;
	glDisable(GL_FOG);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}
void prevFogState()
{
	if(fogActive == 1)
		glEnable(GL_FOG);
	else
		glDisable(GL_FOG);
}
void setFogColor(GLuint colorEnum)
{
	glFogfv(GL_FOG_COLOR, fogColor[colorEnum]);
	glClearColor(fogColor[colorEnum][0], fogColor[colorEnum][1], fogColor[colorEnum][2], fogColor[colorEnum][3]); 
	currentFogColor = colorEnum;
}
void setFogDensity(GLfloat density)
{
	glFogf(GL_FOG_DENSITY, density);
}
void setFogStartEnd(GLfloat start, GLfloat end)
{
	glFogf(GL_FOG_START, start);
	glFogf(GL_FOG_END, end);
}
void setFogMode(GLint mode)
{
	glFogi(GL_FOG_MODE, mode);
}