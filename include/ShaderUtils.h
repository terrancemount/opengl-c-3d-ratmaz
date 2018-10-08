/*
   File: ShaderUtils.h
   Author: David Meyers
   Created: 6 June 2005
   Modified: 30 June 2005
   Purpose: Utilities for programmable shader implementation
 */

extern void printOpenGLError();

extern GLint getUniLoc(GLhandleARB program, const GLcharARB *name);

extern void printInfoLog(GLhandleARB obj);

extern const GLcharARB **fileToStringArray(GLint *nLines, char *FileName);
