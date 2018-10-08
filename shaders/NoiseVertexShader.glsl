/*
  File: NoiseVertexShader.glsl
  Author: David Meyers
  Created:  30 June 2005
  Modified: 30 June 2005
  Purpose: Vertex shader for shading using noise functions. From the Orange
	   Book. Useful for multiple noise-based shaders (the difference is in
	   the Fragment shader). See page 304, Orange Book.
 */

uniform vec3 LightPosition;
uniform float Scale;

varying float LightIntensity;
varying vec3 MCposition;

void main(void)
{
  vec3 ecPosition = vec3 (gl_ModelViewMatrix * gl_Vertex);
  MCposition = vec3(gl_Vertex) * Scale;

  vec3 tnorm      = normalize(vec3(gl_NormalMatrix * gl_Normal));

  LightIntensity = dot(normalize(LightPosition - ecPosition), tnorm);
  LightIntensity *= 1.5;


  gl_Position = ftransform();
}
