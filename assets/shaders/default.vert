#version 150
in vec4 position;
in vec3 normal;
in vec2 texCoord;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

out vec3 viewPosition;
out vec3 viewNormal;
out vec2 pixelTexCoord;

void main()
{
	pixelTexCoord = texCoord;
	vec4 pos = modelViewMatrix * position;
	viewPosition = pos.xyz;
	viewNormal = normalize(normalMatrix * normal);
	gl_Position = projectionMatrix * pos;
}