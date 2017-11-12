
#ifndef EDS_TEXT_H
#define EDS_TEXT_H

#include "GL/glew.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "FreeImage.h"
#include <string>

class EDS_Text
{
public:
	EDS_Text();
	EDS_Text(const char* path);
	~EDS_Text();
	GLuint createTexture(const char* text, GLfloat* scale = NULL);
	GLubyte* getChar(char c, GLuint* pWidth, GLuint* pHeight, bool makeEven = true);
private:
	void init();

	FT_Library ftlib;
	FT_Face fontInfo;
	std::string fontPath;
};




#endif //EDS_TEXT_H
