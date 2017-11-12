
#ifndef EDS_ENTITY_H
#define EDS_ENTITY_H

#include "Entity_Util.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include "EDS_Shader.h"
#include "EDS_Text.h"

class EDS_Entity
{
public:
	EDS_Entity();
	~EDS_Entity();

	virtual void draw();
	virtual int size();

	bool checkBounds(struct PointF point);
	void setPos(float x, float y);
	virtual void mouseClick(int button, int state);
	virtual bool passiveMotion(struct PointF mouse_pos);
	struct PointF getPos();
	bool isMoveable();
	bool snap();
	void setColor(float r, float g, float b);
	void setColor(float r, float g, float b, float* );

protected:
	void setVertex(int i, GLfloat x, GLfloat y, GLfloat* ptr);
	void setSize(GLfloat width, GLfloat height);
	void setupShader(const char* vert_path, const char* frag_path, EDS_Shader* shader, GLuint* texID, GLfloat* colorData);
	void init();

	struct Rectangle bounding;
	PointF center;
	bool moveable;
	bool mouse_snap;
	GLfloat vertArray[2 * 4];
	GLfloat texCoords[2 * 4];
	GLfloat colorArray[4][3];
	GLuint vertBuffID;
	GLuint colorBuffID;
	GLuint texBuffID;
	GLuint shaderID;
	GLuint textureID, textureID2;
	GLint isText;
	EDS_Shader itemShader;
	GLfloat* modelview_matrix;
	GLfloat* projection_matrix;
	int vertexCount;
	Color3i color;

	std::string vert_shader = TRANSPOSE_VERT_PATH;
	std::string frag_shader = FILL_FRAG_PATH;

	EDS_Shader shaders[5];
	GLuint shaderCount;
	EDS_Shader shader1;
	EDS_Shader shader2;

	EDS_Text textObject;
};


#endif //EDS_ENTITY_H
