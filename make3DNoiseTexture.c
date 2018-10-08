/*
  File: make3DNoiseTexture.c
  Author: Orange Book code
  Created: 30 June 2005 (typed in from book)
  Modified: 26 July 2005 by David Meyers. Used source code from Orange Book
            website as well as that in the book. Modifications of the file
	    Noise.cpp from that website.
  Purpose: create a 3D texture using a Perlin noise function. 
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "include/ShaderUtils.h"

int noise3DTexSize = 128;
//GLuint noise3DTexName = 0;
GLubyte * noise3DTexPtr;

int start;
int B;
int BM;

#define MAXB 0x100
#define N 0x1000
#define NP 12   // 2^N
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i, b0, b1, r0, r1)\
        t = vec[i] + N;\
        b0 = ((int)t) & BM;\
        b1 = (b0+1) & BM;\
        r0 = t - (int)t;\
        r1 = r0 - 1.;
#define at2(rx, ry) ( rx * q[0] + ry * q[1] )
#define at3(rx, ry, rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

static int p[MAXB + MAXB + 2];
static double g3[MAXB + MAXB + 2][3];
static double g2[MAXB + MAXB + 2][2];
static double g1[MAXB + MAXB + 2];

void setNoiseFrequency(int frequency)
{
	start = 1;
	B = frequency;
	BM = B-1;
}

void normalize2(double v[2])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

void normalize3(double v[3])
{
	double s;

	s = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

void initNoise()
{
	int i, j, k;

	srand(30757);
	for (i = 0; i < B; i++)
	{
		p[i] = i;
		g1[i] = (double)((rand() % (B + B)) - B) / B;

		for (j = 0; j < 2; j++)
			g2[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);

		for (j = 0; j < 3; j++)
			g3[i][j] = (double)((rand() % (B + B)) - B) / B;
		normalize3(g3[i]);
	}

	while (--i)
	{
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0; i < B + 2; i++)
	{
		p[B + i] = p[i];
		g1[B + i] = g1[i];
		for (j = 0; j < 2; j++)
			g2[B + i][j] = g2[i][j];
		for (j = 0; j < 3; j++)
			g3[B + i][j] = g3[i][j];
	}
}

double noise3(double vec[3])
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	int i, j;

	if (start)
	{
		start = 0;
		initNoise();
	}

	setup(0, bx0, bx1, rx0, rx1);
	setup(1, by0, by1, ry0, ry1);
	setup(2, bz0, bz1, rz0, rz1);

	i = p[bx0];
	j = p[bx1];

	b00 = p[i + by0];
	b10 = p[j + by0];
	b01 = p[i + by1];
	b11 = p[j + by1];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[b00 + bz0]; u = at3(rx0, ry0, rz0);
	q = g3[b10 + bz0]; v = at3(rx1, ry0, rz0);
	a = lerp(t, u, v);

	q = g3[b01 + bz0]; u = at3(rx0, ry1, rz0);
	q = g3[b11 + bz0]; v = at3(rx1, ry1, rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[b00 + bz1]; u = at3(rx0, ry0, rz1);
	q = g3[b10 + bz1]; v = at3(rx1, ry0, rz1);
	a = lerp(t, u, v);

	q = g3[b01 + bz1]; u = at3(rx0, ry1, rz1);
	q = g3[b11 + bz1]; v = at3(rx1, ry1, rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return lerp(sz, c, d);
}

void make3DNoiseTexture(void)
{
  int f, i, j, k, inc;
  int startFrequency = 4;
  int numOctaves = 4;
  double ni[3];
  double inci, incj, inck;
  int frequency = startFrequency;
  GLubyte *ptr;
  double amp = 0.5;
  int textureSize = 4 * noise3DTexSize * noise3DTexSize * noise3DTexSize; //*
    // sizeof(GLubyte);

  if((noise3DTexPtr = (GLubyte *) malloc(textureSize)) == NULL)
  {
    fprintf(stderr,"ERROR: make3DNoiseTexture could not allocate space\n");
    exit(1);
  }
  else fprintf(stderr,"Allocated %d bytes for texture\n", textureSize);
    
  for(f=0, inc=0; f<numOctaves; ++f, frequency *= 2, ++inc, amp *= 0.5)
    {
      setNoiseFrequency(frequency);
      ptr = noise3DTexPtr;
      ni[0] = ni[1] = ni[2] = 0;
      
      inci = 1.0 / (noise3DTexSize / frequency);
      for (i = 0; i < noise3DTexSize; ++i, ni[0] += inci)
	{
	  incj = 1.0 / (noise3DTexSize / frequency);
	  for (j = 0; j < noise3DTexSize; ++j, ni[1] += incj)
	    {
	      inck = 1.0 / (noise3DTexSize / frequency);
	      for (k = 0; k < noise3DTexSize; ++k, ni[2] += inck, ptr += 4)
		{
		  *(ptr + inc) = (GLubyte) (((noise3(ni) + 1.0) * amp) * 128.0);
		  //		  if(f == 3 && i == 127 && j == 127)
		  //		    fprintf(stderr,"amp = %f, noise3(ni)=%f, value=%f\n",
		  //			    amp, noise3(ni), (noise3(ni)+1.0) * amp * 128.0);
		}
	    }
	}
    }
  
}


void init3DNoiseTexture(int texSize, GLubyte* texPtr,
			GLuint *textureName)
{
  glGenTextures(1, textureName);
  printOpenGLError();
  fprintf(stderr,"Texture name generated: %u\n", *textureName);
  fprintf(stderr,"Texture size: %d\n", texSize);

  glActiveTexture(GL_TEXTURE0);//assuming no active textures here...
  printOpenGLError();
  glBindTexture(GL_TEXTURE_3D, *textureName);
  printOpenGLError();

  glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  printOpenGLError();
  glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  printOpenGLError();
  glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  printOpenGLError();
  glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  printOpenGLError();
  glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  printOpenGLError();
  glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA,
	       texSize, texSize, texSize,
	       0, GL_RGBA, GL_UNSIGNED_BYTE, texPtr);
  printOpenGLError();

  //  free(texPtr);
}

void CreateNoise3D(GLuint *textureName)
{
  //int i;

   make3DNoiseTexture();
  /*
  for(i=0; i<noise3DTexSize; i++)
    fprintf(stderr,"noise3DTexPtr[%d]=%u\n",
	    i,noise3DTexPtr[i]);
  */
   init3DNoiseTexture(noise3DTexSize, noise3DTexPtr, textureName);
}
