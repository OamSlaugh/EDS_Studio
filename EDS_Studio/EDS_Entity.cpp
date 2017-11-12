
#include "EDS_Entity.h"
#include "ShaderManager.h"
#include "TextureManager.h"

EDS_Entity::EDS_Entity()
{
	bounding.width = 0.5f;
	bounding.height = 0.5f;
	init();
}

void EDS_Entity::init()
{
	center.x = 0.0f;
	center.y = 0.0f;

	moveable = true;
	mouse_snap = false;

	vertexCount = 4;

	setSize(bounding.width, bounding.height);

	setVertex(0, 0.0f, 0.0f, texCoords);
	setVertex(1, 1.0f, 0.0f, texCoords);
	setVertex(2, 1.0f, 1.0f, texCoords);
	setVertex(3, 0.0f, 1.0f, texCoords);

	modelview_matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16);
	projection_matrix = (GLfloat*)malloc(sizeof(GLfloat) * 16);
}

void EDS_Entity::setSize(GLfloat width, GLfloat height)
{
	setVertex(0, -width / 2, -height / 2, vertArray);
	setVertex(1, width / 2, -height / 2, vertArray);
	setVertex(2, width / 2, height / 2, vertArray);
	setVertex(3, -width / 2, height / 2, vertArray);
}

void EDS_Entity::setupShader(const char* vert_path, const char* frag_path, EDS_Shader* shader, GLuint* texID, GLfloat* colorData)
{
	GLuint vertBuff, colorBuff, texBuff;
	glGenBuffers(1, &vertBuff);
	glGenBuffers(1, &colorBuff);
	glGenBuffers(1, &texBuff);
	glBindBuffer(GL_ARRAY_BUFFER, texBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 4, texCoords, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 4, vertArray, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuff);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4, colorData, GL_STATIC_DRAW);

	shader->createProgram(vert_path, frag_path);
	shader->addBuffer("a_Color", colorBuff, 3, GL_FLOAT);
	shader->addBuffer("a_Vertex", vertBuff, 2, GL_FLOAT);
	shader->addBuffer("a_TexCoord0", texBuff, 2, GL_FLOAT);
	

	shader->addTexture("texture0", texID);
	shader->addUniform4x4("modelview_matrix", modelview_matrix);
	shader->addUniform4x4("projection_matrix", projection_matrix);
}

EDS_Entity::~EDS_Entity()
{
	//free(modelview_matrix);
	//free(projection_matrix);
}

void EDS_Entity::setVertex(int i, GLfloat x, GLfloat y, GLfloat* ptr)
{
	ptr[i * 2] = x;
	ptr[i * 2 + 1] = y;
}

int EDS_Entity::size()
{
	return sizeof(EDS_Entity);
}

void EDS_Entity::setColor(float r, float g, float b)
{
	for (int i = 0; i < vertexCount; i++)
	{
		colorArray[i][0] = r;
		colorArray[i][1] = g;
		colorArray[i][2] = b;
	}
}

void EDS_Entity::setColor(float r, float g, float b, float* buff)
{
	for (int i = 0; i < vertexCount; i++)
	{
		buff[i * 3] = r;
		buff[i * 3 + 1] = g;
		buff[i * 3 + 2] = b;
	}
}

void EDS_Entity::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(center.x, center.y, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);

	for (GLuint i = 0; i < shaderCount; i++)
	{
		shaders[i].activate();
		shaders[i].batch();
		shaders[i].deactivate();
	}
}

bool EDS_Entity::checkBounds(struct PointF point)
{
	float dx = (point.x - center.x);
	float dy = (point.y - center.y);

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;

	if ((dx < (bounding.width / 2)) && (dy < (bounding.height / 2)))
	{
		return true;
	}
	
	return false;
}

void EDS_Entity::setPos(float x, float y)
{
	center.x = x;
	center.y = y;
}

void EDS_Entity::mouseClick(int button, int state)
{

}

bool EDS_Entity::passiveMotion(struct PointF mouse_pos)
{
	return false;
}

struct PointF EDS_Entity::getPos()
{
	return center;
}

bool EDS_Entity::isMoveable()
{
	return moveable;
}

bool EDS_Entity::snap()
{
	return mouse_snap;
}
