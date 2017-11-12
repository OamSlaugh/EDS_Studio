#version 330

uniform sampler2D texture0;
uniform int isText;

in vec4 color;
in vec4 position;
in vec2 texCoord0;

out vec4 outColor;
int x, y, i;

void main(void)
{
	outColor = texture(texture0, texCoord0.st);
}
