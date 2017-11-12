
#include "EDS_Entity.h"
#include "ShaderManager.h"

EDS_Entity::EDS_Entity()
{
	center.x = 0.0f;
	center.y = 0.0f;
	bounding.width = 0.5f;
	bounding.height = 0.5f;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	moveable = true;
	mouse_snap = false;

	setVertex(0, -0.25f, -0.25f, vertArray);
	setVertex(1, 0.25f, -0.25f, vertArray);
	setVertex(2, 0.25f, 0.25f, vertArray);
	setVertex(3, -0.25f, 0.25f, vertArray);
	//glGenBuffersARB(1, &vertBuffID);
	//glewInit();
	//glGenBuffers = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress((const char*)"glGenBuffers");
	glGenBuffers(1, &vertBuffID);
	glGenBuffers(1, &colorBuffID);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * 4, vertArray, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, colorBuffID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, colorArray, GL_STATIC_DRAW);
	shaderID = ShaderManager::create_program("shaders\\vert.shader", "shaders\\frag.shader");
}

EDS_Entity::~EDS_Entity()
{

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

void EDS_Entity::draw()
{
	GLfloat modelview_matrix[16];
	GLfloat projection_matrix[16];

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(center.x, center.y, 0.0f);

	glColor3ub(color.r, color.g, color.b);
	colorArray[0] = 1.0f;
	colorArray[1] = 0.0f;
	colorArray[2] = 0.0f;
	glUseProgram(shaderID);
	GLuint modelview_location = glGetUniformLocation(shaderID, "modelview_matrix");
	GLuint projection_location = glGetUniformLocation(shaderID, "projection_matrix");
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix);
	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix);

	//glBindAttribLocation(shaderID, 0, "a_Vertex");
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffID);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);

	//glBindAttribLocation(shaderID, 1, "a_Color");
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3, colorArray, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorBuffID);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);

	glUniformMatrix4fv(modelview_location, 1, false, &modelview_matrix[0]);
	glUniformMatrix4fv(projection_location, 1, false, &projection_matrix[0]);

	glDrawArrays(GL_POLYGON, 0, 4);

	/*glBindBuffer(GL_ARRAY_BUFFER, colorBuffID);
	glColorPointer(1, GL_FLOAT, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffID);
	glVertexPointer(2, GL_FLOAT, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POLYGON, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
	*/
	glutSwapBuffers();
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	//glUseProgram(0);
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
