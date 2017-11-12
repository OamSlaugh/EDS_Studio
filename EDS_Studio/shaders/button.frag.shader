#version 330

uniform sampler2D texture0;

in vec4 color;
in vec4 position;
in vec2 texCoord0;

out vec4 outColor;
int x, y, i;

void main(void)
{
	//outColor = vec4(color.rgb, 0.1);
	outColor = color;

	x = int(texCoord0.s * 300);
	y = int(texCoord0.t * 300);

	if ((y <= 5) || (y >= 295) || (x <= 2) || (x >= 298))
	{
		outColor = vec4(0.0,0.0,0.0,1.0);
	}
}
