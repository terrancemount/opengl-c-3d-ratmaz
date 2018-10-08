/*
   File: InstallShaders.h
   Author: David Meyers
   Created: 6 June 2005
   Modified: 22 July 2005
   Purpose: Install programmable vertex and fragment shaders.
 */

GLhandleARB installShaders(const GLcharARB **vertexShader, 
				int vLineCount,
				const GLcharARB **fragmentShader, 
				int fLineCount);
