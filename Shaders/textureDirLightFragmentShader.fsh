#version 330 core

in vec3 normalVert;
in vec2 UV;
in vec3 tangentVert;

out vec4 outputColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightDirection;
uniform vec4 diffuseLightCol;
uniform vec3 ambLightCol;
uniform float ambIntensity;

void main() 
{
	vec3 lightDir;
	float lightIntensity;
	
	
	//vec3 tangent = normalize(tangentVert);
	
	//tangent = normalize(tangent- dot(tangent, normal) * normal);
	
	//vec3 biNormal = cross(tangent, normal);
	//vec3 bumpNormal = texture(myTextureSampler, UV).xyz;
	//bumpNormal = 2.0 * bumpNormal - vec3(1.0, 1.0, 1.0);
	//vec3 newNormal;
	//mat3 tbn = mat3(tangent, biNormal, normal);
	//newNormal = tbn * bumpNormal;
	//newNormal = normalize(newNormal);
	
	// invert the light direction for calculations
	lightDir = -lightDirection;
	
	
	float xGradient = texture(texture0, vec2(UV.x - 1, UV.y)).x - texture(texture0, vec2(UV.x + 1, UV.y)).x;
	float yGradient = texture(texture0, vec2(UV.x, UV.y - 1)).y - texture(texture0, vec2(UV.x, UV.y + 1)).y;
	
	//vec3 norm = vec3(b-a, c-a, 0.1);
	//lightDir = 2.0 * (lightDir.rgb - 0.5);
	vec3 norm = 2.0 * (texture(texture0, UV).rgb - 0.5) * normalVert;
	//vec3 norm = normalVert + (UV.x * xGradient) + (UV.y * yGradient);
	
	normalize(norm);
	//vec3 newNormal = texture( texture0, UV ).rgb * normalVert;
	vec3 newNormal = norm;
	
	// Calculate the amount of light on this pixel
	//lightIntensity = clamp(dot(normalVert, lightDir), 0.0f, 1.0f);
	lightIntensity = clamp(dot(newNormal, lightDir), 0.0f, 1.0f);
	
	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity
	outputColor = clamp((diffuseLightCol * lightIntensity), 0.0f, 1.0f);
	
	// Multiple the light colour with the object's diffuse colour to get final result
	outputColor = vec4(texture( texture0, UV ).rgb, 1) * outputColor + vec4((ambLightCol * ambIntensity), 1);
}