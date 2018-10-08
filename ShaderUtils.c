/*
   File: ShaderUtils.c
   Author: David Meyers
   Created: 6 June 2005
   Modified: 20 July 2005
   Purpose: Utilities for programmable shader implementation
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>

void printOpenGLError()
{
  GLenum errorCode = glGetError();

  switch(errorCode)
    {
    case GL_NO_ERROR: return;
      break;
    case GL_INVALID_ENUM: printf("Invalid enum\n");
      break;
    case GL_INVALID_VALUE: printf("Invalid value\n");
      break;
    case GL_INVALID_OPERATION: printf("Invalid operation\n");
      break;
    case GL_STACK_OVERFLOW: printf("Stack overflow\n");
      break;
    case GL_STACK_UNDERFLOW: printf("Stack underflow\n");
      break;
    case GL_OUT_OF_MEMORY: printf("Out of memory\n");
      break;
      // case GL_TABLE_TOO_LARGE: printf("Table too large\n");
      // break;
    default: printf("unknown errorCode value\n");
    }
}

GLint getUniLoc(GLhandleARB program, const GLcharARB *name)
{
  GLint loc;

  loc = glGetUniformLocationARB(program, name);
  if(loc == -1) printf("No such uniform named \'%s\'\n", name);
  printOpenGLError();
  return loc;
}

void printInfoLog(GLhandleARB obj)
{
  int infologLength = 0;
  int charsWritten = 0;
  GLcharARB *infoLog;
  printf("printInfoLog:\n\topenGL error: ");
  printOpenGLError();
  printf("\n");

  glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB,
			    &infologLength);
  printf("printInfoLog:\n\topenGL error: ");
  printOpenGLError();
  printf("\n");

  if(infologLength > 0)
    {
      infoLog = (GLcharARB*) malloc(infologLength);
      if(infoLog == NULL)
	{
	  printf("Error: could not allocate InfoLog buffer\n");
	  exit(1);
	}
      glGetInfoLogARB(obj, infologLength, &charsWritten, infoLog);
      printf("InfoLog:\n%s\n\n", infoLog);
      free(infoLog);
    }
  printf("printInfoLog:\n\topenGL error: ");
  printOpenGLError();
  printf("\n");
}

const GLcharARB **fileToStringArray(GLint *nLines, char *FileName)
{
  GLcharARB **a;
  const GLcharARB **returnVal;
  FILE *in;
  char *inputLine = (char *)malloc (1024*sizeof(char));
  char *endOfFile;//null when end of file reached
  int i;

  in = fopen(FileName, "r");
  if(in == NULL)
    {
      fprintf(stderr,"fileToStringArray: error opening file %s\n", FileName);
      exit(-1);
    }
  *nLines = 0;

  endOfFile = fgets(inputLine, 1024, in);
  while(!feof(in))
    {
      *nLines += 1;
      endOfFile = fgets(inputLine, 1024, in);
    }
  in = freopen(FileName, "r", in);
  if(in == NULL)
    {
      fprintf(stderr,"fileToStringArray: error opening file %s\n", FileName);
      exit(-1);
    }
  a = (GLcharARB **) malloc(*nLines * sizeof(GLcharARB *));
  for(i=0; i<*nLines; i++)
    {
      endOfFile = fgets(inputLine, 1024, in);
      a[i] = (GLcharARB *) malloc((strlen(inputLine)+1) * sizeof(GLcharARB));
      strcpy(a[i],inputLine);
    }
  fclose(in);
  returnVal = (const GLcharARB **) a;
  return returnVal;
}
