
#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "GL\glew.h"
#include <vector>

class ShaderManager
{
public:
	static GLuint load_shader(const char* path, GLenum type);
	static GLuint create_program(const char* vert_path, const char* frag_path);
	static void use_shader(GLuint shaderID);
	static void disable_shader();
private:
	static void read_src(const char* path, std::vector<char> &buffer);
};

#endif //SHADER_MANAGER_H
