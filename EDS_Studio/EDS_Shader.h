
#ifndef EDS_SHADER_H
#define EDS_SHADER_H

#include <GL/glew.h>
#include "ShaderManager.h"
#include <vector>
#include <string>

enum UniformType
{
	TYPE_MAT_4X4F = 0,
	TYPE_TEX_2D,
	TYPE_INT
};

struct ShaderAttrib
{
	GLuint location;
	GLuint size;
	GLuint buffID;
	GLenum type;
	std::string name;
};

class EDS_Shader
{
public:
	EDS_Shader();
	~EDS_Shader();
	void createProgram(const char* vert, const char* frag);
	void activate();
	void deactivate();
	void sendUniform4x4(const char* name, GLfloat* data);
	GLuint addUniformI(const char* name, GLint* data);
	GLuint addUniform4x4(const char* name, GLfloat* data);
	GLuint addTexture(const char* name, GLuint* id);
	GLint getBuffer(const char* name, GLuint* size = NULL);
	void addBuffer(const char* name, GLuint buffID, GLint size, GLenum type = GL_FLOAT);
	void draw(GLuint count, GLenum mode = GL_POLYGON);
	void removeBuffers();
	void batch();
private:

	GLuint pushUniformData(const char* name, void* data, enum UniformType type);
	GLuint shaderID;
	std::vector<struct ShaderAttrib> attributes;
	std::vector<GLuint> uniform_IDs;
	std::vector<void*> uniform_data;
	std::vector<enum UniformType> uniform_types;
};

#endif
