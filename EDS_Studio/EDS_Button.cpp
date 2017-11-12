
#include "EDS_Button.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "GL/wglew.h"

EDS_Button::EDS_Button()
{
	initButton();
}

EDS_Button::EDS_Button(int width, int height, const char* pText)
{
	text = pText;
	bounding.width = width / COORDINATE_RATIO;
	bounding.height = height / COORDINATE_RATIO;
	initButton();
}

EDS_Button::~EDS_Button()
{

}

void EDS_Button::initButton()
{
	GLfloat ratio;
	shaderCount = 0;
	vert_shader = TRANSPOSE_VERT_PATH;
	frag_shader = BUTTON_FRAG_PATH;

	init();

	colorReleased = { 0, 122, 204 };
	colorPressed = { 153, 217, 234 };
	colorHover = { 100, 143, 247 };
	textColor = { 30, 30, 30 };

	color = colorReleased;
	
	setColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	setupShader(vert_shader.c_str(), frag_shader.c_str(), &shaders[shaderCount],&textureID, &colorArray[0][0]);
	colorBuff = shaders[shaderCount].getBuffer("a_Color");
	shaderCount++;

	if (text.length() > 0)
	{
		setColor(textColor.r / 255.0f, textColor.g / 255.0f, textColor.b / 255.0f);
		textureID = textObject.createTexture(text.c_str(), &ratio);

		if (bounding.height / ratio < bounding.width)
		{
			setSize(bounding.height / ratio, bounding.height);
		}
		else
		{
			setSize(bounding.width, bounding.width * ratio);
		}
		
		frag_shader = TEXT_FRAG_PATH;
		setupShader(vert_shader.c_str(), frag_shader.c_str(), &shaders[shaderCount], &textureID, &colorArray[0][0]);
		shaderCount++;
	}

	pressed = false;
	onPress = NULL;
	onRelease = NULL;

	moveable = false;
	mouse_snap = false;
}

void EDS_Button::updateColor(Color3i _color, bool update)
{
	if (update == true)
	{
		setColor(_color.r / 255.0f, _color.g / 255.0f, _color.b / 255.0f);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuff);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat)*4*3, &colorArray[0][0]);
		newColor = false;
	}
}

void EDS_Button::draw()
{
	updateColor(color, newColor);

	EDS_Entity::draw();
}

void EDS_Button::mouseClick(int button, int state)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			pressed = true;
			color = colorPressed;
			newColor = true;
			if (onPress != NULL)
				onPress();
		}
		else
		{
			pressed = false;
			color = colorReleased;
			newColor = true;
			if (onRelease != NULL)
				onRelease();
		}
	}
}

bool EDS_Button::passiveMotion(struct PointF mouse_pos)
{
	bool redraw_required = false;
	struct Color3i old_color;

	old_color = color;

	if (checkBounds(mouse_pos))
	{
		color = colorHover;
	}
	else
	{
		color = colorReleased;
	}

	if ((old_color.r != color.r) || (old_color.g != color.g) || (old_color.b != color.b))
	{
		redraw_required = true;
		newColor = true;
	}

	return redraw_required;
}

void EDS_Button::setPressEvent(void(*callback)())
{
	onPress = callback;
}

void EDS_Button::setReleaseEvent(void(*callback)())
{
	onRelease = callback;
}

bool EDS_Button::isPressed()
{
	return pressed;
}
