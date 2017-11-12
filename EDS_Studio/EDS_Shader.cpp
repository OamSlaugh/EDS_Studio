
#include "EDS_Shader.h"
#include <string>

EDS_Shader::EDS_Shader()
{

}

EDS_Shader::~EDS_Shader()
{

}

void EDS_Shader::createProgram(const char* vert, const char* frag)
{
	shaderID = ShaderManager::create_program(vert, frag);
}

void EDS_Shader::activate()
{
	glUseProgram(shaderID);
}

void EDS_Shader::deactivate()
{
	glUseProgram(0);
}

void EDS_Shader::sendUniform4x4(const char* name, GLfloat* data)
{
	GLuint location;

	location = glGetUniformLocation(shaderID, name);
	glUniformMatrix4fv(location, 1, false, &data[0]);
}

GLuint EDS_Shader::addUniform4x4(const char* name, GLfloat* data)
{
	return pushUniformData(name, data, TYPE_MAT_4X4F);
}

GLuint EDS_Shader::addUniformI(const char* name, GLint* data)
{
	return pushUniformData(name, data, TYPE_INT);
}

GLuint EDS_Shader::addTexture(const char* name, GLuint* id)
{
	return pushUniformData(name, id, TYPE_TEX_2D);
}

void EDS_Shader::addBuffer(const char* name, GLuint buffID, GLint size, GLenum type)
{
	struct ShaderAttrib attribute;

	activate();

	attribute.location = glGetAttribLocation(shaderID, name);
	glBindAttribLocation(shaderID, attribute.location, name);

	attribute.buffID = buffID;
	attribute.size = size;
	attribute.type = type;
	attribute.name = name;

	attributes.push_back(attribute);
}

GLint EDS_Shader::getBuffer(const char* name, GLuint* size)
{
	for (int i = 0; i < attributes.size(); i++)
	{
		if (attributes[i].name.compare(name) == 0)
		{
			if (size != NULL)
			{
				*size = attributes[i].size;
			}
			return attributes[i].buffID;
		}
	}

	return -1;
}

void EDS_Shader::draw(GLuint count, GLenum mode)
{
	glDrawArrays(mode, 0, count);
}

void EDS_Shader::removeBuffers()
{
	for (int i = (int)attributes.size() - 1; i >= 0; i--)
	{
		glDisableVertexAttribArray(attributes[i].location);
		attributes.pop_back();
	}
}

void EDS_Shader::batch()
{
	GLuint id;
	GLint data;

	glLinkProgram(shaderID);
	glUseProgram(shaderID);

	for (int i = 0; i < (int)uniform_IDs.size(); i++)
	{
		switch (uniform_types[i])
		{
		case TYPE_MAT_4X4F:
			glUniformMatrix4fv(uniform_IDs[i], 1, false, (GLfloat*)uniform_data[i]);
			break;
		case TYPE_INT:
			data = *(GLint*)uniform_data[i];
			glUniform1i(uniform_IDs[i], data);
		case TYPE_TEX_2D:
			glActiveTexture(GL_TEXTURE0);
			id = *(GLuint*)uniform_data[i];
			glBindTexture(GL_TEXTURE_2D, *(GLuint*)uniform_data[i]);
			glUniform1i(uniform_IDs[i], 0);
		default:
			break;
		}
	}

	for (int i = 0; i < attributes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, attributes[i].buffID);
		glVertexAttribPointer(attributes[i].location, attributes[i].size, attributes[i].type, false, 0, 0);
		glEnableVertexAttribArray(attributes[i].location);
	}

	draw(4,GL_TRIANGLE_FAN);

	for (int i = 0; i < attributes.size(); i++)
	{
		glDisableVertexAttribArray(attributes[i].location);
	}
}

GLuint EDS_Shader::pushUniformData(const char* name, void* data, enum UniformType type)
{
	GLuint location;
	location = glGetUniformLocation(shaderID, name);
	uniform_IDs.push_back(location);
	uniform_data.push_back(data);
	uniform_types.push_back(type);

	return location;
}