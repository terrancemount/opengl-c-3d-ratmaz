/*
  File: SkyFragmentShader.glsl
  Author: David Meyers
  Created:  30 June 2005
  Modified: 4 November 2005
  Purpose: Fragment shader for simulating a cloudy sky.. From the Orange
	   Book. See page 305, Orange Book. Added offset to animate, see page 317
 */


varying float LightIntensity;
varying vec3 MCposition;

uniform sampler3D Noise;
uniform vec3 SkyColor;
uniform vec3 CloudColor;
uniform vec3 Offset;

void main(void)
{
  vec4 noiseVec = texture3D(Noise, MCposition + Offset);
  float intensity = (noiseVec[0] + noiseVec[1] + noiseVec[2] + noiseVec[3]
                     + 0.03125) * 1.5;
      
 //float intensity = 0.03125 * 1.5;

  vec3 color = mix(SkyColor, CloudColor, intensity) * LightIntensity;
  gl_FragColor = vec4(color, 1.0);

}


