#version 330 core

// Updated to support a single point light source

uniform mat4 projViewMatrix;
uniform mat4 worldMatrix;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

// main routine
void main()
{
	gl_Position = projViewMatrix * worldMatrix * vec4(vertexPosition_modelspace, 1.0);
	
	UV = vertexUV;
}