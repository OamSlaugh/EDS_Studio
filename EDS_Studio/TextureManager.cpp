
#include "TextureManager.h"

void TextureManager::initialize()
{
	FreeImage_Initialise(true);
}

void TextureManager::close()
{
	FreeImage_DeInitialise();
}

GLuint TextureManager::loadTexture(const char* path)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path);

	FIBITMAP* bitmap = FreeImage_Load(format, path);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32;

	if (bitsPerPixel != 32)
	{
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	else
	{
		bitmap32 = bitmap;
	}

	int width = FreeImage_GetWidth(bitmap32);
	int height = FreeImage_GetWidth(bitmap32);

	GLubyte* textureData = FreeImage_GetBits(bitmap32);
	return loadBitmap(textureData, width, height);
}

GLuint TextureManager::loadBitmap(GLubyte* data, int width, int height, GLenum format)
{
	GLuint tempTextureID;

	glGenTextures(1, &tempTextureID);
	glBindTexture(GL_TEXTURE_2D, tempTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

	return tempTextureID;
}
