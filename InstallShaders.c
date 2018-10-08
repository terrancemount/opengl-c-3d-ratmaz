/*
   File: InstallShaders.c
   Author: David Meyers
   Created: 3 June 2005
   Modified: 22 July 2005
   Purpose: Install vertex and fragment shaders. The shaders themselves
            are defined in separate files
 */

#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "include/ShaderUtils.h"

GLhandleARB installShaders(const GLcharARB **vertexShader,
				int vLineCount,
				const GLcharARB **fragmentShader,
				int fLineCount)
{
  GLhandleARB VS, FS, Prog;
  GLint vertCompiled, fragCompiled;
  GLint linked;

  fprintf(stderr,"Entering installShaders\n");

  VS = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
  FS = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);

  fprintf(stderr,"Created shader objects\n");

  glShaderSourceARB(VS, vLineCount, vertexShader, NULL);

  fprintf(stderr,"Specified vertex shader source\n");

  glShaderSourceARB(FS, fLineCount, fragmentShader, NULL);

  fprintf(stderr,"Specified fragment shader source\n");

  glCompileShaderARB(VS);
  fprintf(stderr,"Compiled VS\n");

  printOpenGLError();
  glGetObjectParameterivARB(VS, GL_OBJECT_COMPILE_STATUS_ARB,
			    &vertCompiled);
  printInfoLog(VS);

  glCompileShaderARB(FS);
  fprintf(stderr,"Compiled FS\n");
  printOpenGLError();
  glGetObjectParameterivARB(FS, GL_OBJECT_COMPILE_STATUS_ARB,
			    &fragCompiled);
  printInfoLog(FS);

  if(!vertCompiled)
    {
      fprintf(stderr,"vertex shader failed to compile.\n");
      return 0;
    }
  if(!fragCompiled)
    {
      fprintf(stderr,"fragment shader failed to compile.\n");
      return 0;
    }

  Prog = glCreateProgramObjectARB();
  glAttachObjectARB(Prog, VS);
  glAttachObjectARB(Prog, FS);

  glLinkProgramARB(Prog);
  printOpenGLError();
  glGetObjectParameterivARB(Prog, GL_OBJECT_LINK_STATUS_ARB, &linked);
  printInfoLog(Prog);

  if(!linked)
    {
      printf("link failed\n");
      return 0;
    }

  fprintf(stderr,"Exiting installShaders\n");
  return Prog;
}
