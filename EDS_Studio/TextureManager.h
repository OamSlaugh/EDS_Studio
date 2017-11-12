
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "FreeImage.h"
#include "GL/glew.h"

class TextureManager
{
public:
	static void initialize();
	static void close();
	static GLuint loadTexture(const char* path);
	static GLuint loadBitmap(GLubyte* data, int width, int height, GLenum format = GL_BGRA);
};

#endif
