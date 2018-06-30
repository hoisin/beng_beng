#version 330 core

#define MAX_LIGHTS 4

in vec4 pos;
in vec3 norm;
in vec2 UV;

out vec3 color;

uniform sampler2D diffuseTextureSampler;

void main() 
{
	vec3 normal = normalize(norm);
	vec3 lightDir = vec3(0,100,0) - pos.xyz;
	float length = length(lightDir);
	
	lightDir = normalize(lightDir);
	
	// Hard coded number is the attenuation value you would pass into the shader
	float atten = clamp((300 - length) / 300, 0, 1);
	
	float lamb = max(dot(normal, lightDir), 0.0) * atten;
	
	vec3 colour = vec3(0.1,0,0) + lamb * texture( diffuseTextureSampler, UV ).rgb;
	
	// output color as texture
	color = colour;

}