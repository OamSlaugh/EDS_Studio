
#include "EDS_Texture.h"
#include "TextureManager.h"

EDS_Texture::EDS_Texture()
{
	filePath = "C:\\Textures\\icon.png";
	init();
}
EDS_Texture::EDS_Texture(const char* file)
{
	filePath = file;
	init();
}

EDS_Texture::~EDS_Texture()
{

}

void EDS_Texture::init()
{
	textureID = TextureManager::loadTexture(filePath.c_str());
}