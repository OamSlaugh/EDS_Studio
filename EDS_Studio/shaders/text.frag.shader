#version 330

uniform sampler2D texture0;

in vec4 color;
in vec4 position;
in vec2 texCoord0;

out vec4 outColor;
int x, y, i;


void main(void)
{
	outColor.a = texture(texture0, texCoord0.st).a;
	outColor.rgb = color.rgb;
}
