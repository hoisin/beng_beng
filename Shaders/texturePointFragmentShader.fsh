#version 330 core

#define MAX_POINT_LIGHTS 20
#define MAX_SPOT_LIGHTS 20

in vec4 pos;
in vec3 norm;
in vec2 UV;

out vec3 color;

uniform sampler2D diffuseTextureSampler;

// Point light uniforms
uniform int activePointLights;
uniform vec3 pointLights[MAX_POINT_LIGHTS];
uniform vec3 lightColor[MAX_POINT_LIGHTS];
uniform float lightIntensity[MAX_POINT_LIGHTS];
uniform float attenuation[MAX_POINT_LIGHTS];

// Spot light uniforms
uniform int activeSpotLights;
uniform vec3 spotLights[MAX_SPOT_LIGHTS];
uniform vec3 spotLightColor[MAX_SPOT_LIGHTS];
uniform vec3 spotLightDir[MAX_SPOT_LIGHTS];
uniform float spotLightIntensity[MAX_SPOT_LIGHTS];
uniform float spotLightAtten[MAX_SPOT_LIGHTS];
uniform float spotLightConeAngle[MAX_SPOT_LIGHTS];

void main() 
{
	vec3 normal = normalize(norm);
	
	// Point lights
	for(int i = 0; i < activePointLights; i++)
	{
		vec3 lightDir = pointLights[i] - pos.xyz;
		float length = length(lightDir);
		lightDir = normalize(lightDir);
		
		float atten = clamp((attenuation[i] - length) / attenuation[i], 0, 1);
		
		float lamb = max(dot(normal, lightDir), 0.0) * atten * lightIntensity[i];
		
		// Accumalate light color
		color += lamb * texture( diffuseTextureSampler, UV).rgb * lightColor[i];
	}
	
	// Spot lights
	for(int j = 0; j < activeSpotLights; j++)
	{
		vec3 surfaceToLight = spotLights[j] - pos.xyz;
		float surfaceToLightLength = length(surfaceToLight);
		surfaceToLight = normalize(surfaceToLight);
		
		// Reverse the light vector to match the surface to light direction for calculating
		vec3 lightVec = normalize(-spotLightDir[j]);
		
		float lightDot = dot(surfaceToLight, lightVec);
		float coneDotAngle = cos(radians(spotLightConeAngle[j]));

		if(lightDot > coneDotAngle)
		{
			float atten = clamp((spotLightAtten[j] - surfaceToLightLength) / spotLightAtten[j], 0, 1);
			float coneAtten = 1.0 - (1.0 - lightDot);
			float lamb = clamp(dot(lightVec, normal), 0, 1) * spotLightIntensity[j] * atten * coneAtten;
			color += lamb * texture( diffuseTextureSampler, UV).rgb * spotLightColor[j];
		}
		else
		{
			// Accumalate ambient only
		}
	}
	
	// Add ambient color if want to..
	//
	//color = vec3(0.1,0,0) + colour;
	//color = texture( diffuseTextureSampler, UV ).rgb;
}