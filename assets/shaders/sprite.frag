#version 150
out vec4 color;

in vec2 pixelTexCoord;

uniform vec4 spriteColor;
uniform sampler2D spriteTexture;

void main()
{
	color = texture(spriteTexture, pixelTexCoord) * spriteColor;
}