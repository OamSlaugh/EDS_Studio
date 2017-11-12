
#ifndef EDS_TEXTURE_H
#define EDS_TEXTURE_H

#include <GL/glew.h>
#include <string>

class EDS_Texture
{
public:
	EDS_Texture();
	EDS_Texture(const char* file);
	~EDS_Texture();
private:
	void init();

	GLuint textureID;
	std::string filePath;
};

#endif //EDS_TEXTURE_H
