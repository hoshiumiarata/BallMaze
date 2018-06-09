#version 150
in vec4 position;
in vec2 texCoord;
uniform mat4 modelMatrix;
uniform vec2 spriteAlign;
uniform vec2 spriteSize;

out vec2 pixelTexCoord;

void main()
{
	pixelTexCoord = texCoord;
	vec4 spritePosition = vec4(spriteSize, 1.0, 1.0) * position + vec4(spriteAlign, 0.0, 0.0);
	gl_Position = modelMatrix * spritePosition * vec4(2.0, -2.0, 0.0, 1.0) - vec4(1.0, -1.0, 0.0, 0.0);
}