#version 330

uniform sampler2D texture0;

in vec4 color;
in vec4 position;
in vec2 texCoord0;

out vec4 outColor;
int x, y, i;

void main(void)
{
	/*outColor = vec4(color.rgb, 0.1);
	x = int(texCoord0.s * 300);
	y = int(texCoord0.t * 300);

	if ((y <= 5) || (y >= 295) || (x <= 5) || (x >= 295))
	{
		outColor = color;
	}

	for (i = 0; i < 10; i++)
	{
		int diff = ((y % 30) - (x % 30));
		if((diff <= 1) && (diff >= -1))
			outColor = color;
	}*/

	outColor = texture(texture0, texCoord0.st);
}
