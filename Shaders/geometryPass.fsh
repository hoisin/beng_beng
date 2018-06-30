#version 330 core

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

layout (location = 0) out vec3 worldPosOut;
layout (location = 1) out vec3 diffuseOut;
layout (location = 2) out vec3 normalOut;
layout (location = 3) out vec3 texCoordOut;

uniform sampler2D gColourMap;

void main()
{
	worldPosOut = vec3(255,255,255);
	diffuseOut = vec3(0,0.5,0.5);//texture(gColourMap, texCoord0).xyz;
	normalOut = normalize(normal0);
	texCoordOut = vec3(texCoord0, 0.0);
}