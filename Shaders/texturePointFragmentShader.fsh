#version 330 core

#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5

in vec4 pos;
in vec3 norm;
in vec2 UV;

out vec3 color;

uniform sampler2D diffuseTextureSampler;
uniform vec3 spotLights[MAX_SPOT_LIGHTS];
uniform vec3 pointLights[MAX_POINT_LIGHTS];
uniform vec3 directionLight;
uniform vec3 ambientLightCol;

void main() 
{
	vec3 normal = normalize(norm);
	vec3 lightDirs[MAX_POINT_LIGHTS];
	lightDirs[0] = vec3(100,50,100);
	lightDirs[1] = vec3(100,50,-100);
	lightDirs[2] = vec3(-100,50,-100);
	lightDirs[3] = vec3(-100,50,100);
	
	vec3 colour = vec3(0,0,0);
	for(int i = 0; i < MAX_POINT_LIGHTS; i++) {
		vec3 lightDir = lightDirs[i] - pos.xyz;
		
		float length = length(lightDir);
		lightDir = normalize(lightDir);
		
		// Hard coded number is the attenuation value you would pass into the shader
		float atten = clamp((150 - length) / 150, 0, 1);
		
		float lamb = max(dot(normal, lightDir), 0.0) * atten; // * intensity;
		
		// Cumulate lighting
		colour += lamb * texture( diffuseTextureSampler, UV ).rgb; // * light colour
	}
	// add ambient colour last
	color = vec3(0.1,0,0) + colour;
	//color = texture( diffuseTextureSampler, UV ).rgb;

}