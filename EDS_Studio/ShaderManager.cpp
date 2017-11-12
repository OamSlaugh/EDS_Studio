
#include "ShaderManager.h"
#include <fstream>
#include <iostream>

GLuint ShaderManager::load_shader(const char* path, GLenum type)
{
	GLuint shader;
	GLint test;
	std::vector<char> buffer;

	read_src(path, buffer);
	const char* src = &buffer[0];

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &test);
	if (!test)
	{
		std::cerr << "Failed to compile shader:" << std::endl;
		std::vector<char> log(512);
		glGetShaderInfoLog(shader, (GLsizei)log.size(), NULL, &log[0]);
		std::cerr << &log[0] << std::endl;
	}

	return shader;
}

GLuint ShaderManager::create_program(const char* vert_path, const char* frag_path)
{
	GLuint vertexShader, fragmentShader, shaderProgram;

	vertexShader = load_shader(vert_path, GL_VERTEX_SHADER);
	fragmentShader = load_shader(frag_path, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glLinkProgram(shaderProgram);

	return shaderProgram;
}

void ShaderManager::use_shader(GLuint shaderID)
{
	glUseProgram(shaderID);
}

void ShaderManager::disable_shader()
{
	glUseProgram(0);
}

void ShaderManager::read_src(const char* path, std::vector<char> &buffer)
{
	std::ifstream file;
	file.open(path, std::ios::binary);

	if (file.is_open())
	{
		file.seekg(0, std::ios::end);
		size_t length = (size_t)file.tellg();

		file.seekg(0, std::ios::beg);

		buffer.resize(length + 1);
		file.read(&buffer[0], length);
		file.close();
		buffer[length] = '\0';
	}
}