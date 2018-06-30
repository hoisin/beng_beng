#version 330 core

// Updated to support a single point light source

uniform mat4 projViewMatrix;
uniform mat4 worldMatrix;
uniform mat4 invWorldMat;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec4 pos;
out vec3 norm;
out vec2 UV;

// main routine
void main()
{
	gl_Position = projViewMatrix * worldMatrix * vec4(vertexPosition_modelspace, 1.0);
	pos = worldMatrix * vec4(vertexPosition_modelspace, 1.0);
	norm = normalize(invWorldMat * vec4(vertexNormal, 1.0)).xyz;
	UV = vertexUV;
}