#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform mat4 worldInvMatrix;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
//layout(location = 2) in vec3 vertexTangent;
//layout(location = 3) in vec2 vertexUV;

// For PNT, remove the tangent vector and comment out the above "vertexUV" and uncomment the one below
layout(location = 2) in vec2 vertexUV;


out vec3 normalVert;
out vec2 UV;
out vec3 tangentVert;

// main routine
void main()
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(vertexPosition_modelspace, 1.0);	
	UV = vertexUV;
	
	// Calculate the normal vector against world matrix only
	normalVert = mat3(worldInvMatrix) * vertexNormal;
	
	// Calculate the tangent
	tangentVert = mat3(worldInvMatrix) * vertexTangent;
	
	// Normalize the normal vector
	normalVert = normalize(normalVert);
}