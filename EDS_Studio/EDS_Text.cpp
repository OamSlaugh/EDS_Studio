
#include "EDS_Text.h"
#include "TextureManager.h"
#include <vector>

EDS_Text::EDS_Text()
{
	fontPath = "C:\\Fonts\\consola.ttf";
	init();
}

EDS_Text::EDS_Text(const char* path)
{
	fontPath = path;
	init();
}

EDS_Text::~EDS_Text()
{

}

void EDS_Text::init()
{
	FT_Init_FreeType(&ftlib);
	FT_New_Face(ftlib, fontPath.c_str(), 0, &fontInfo);
	FT_Set_Char_Size(fontInfo, 0, 72 << 6, 0, 72);
	//FT_Set_Pixel_Sizes(fontInfo, 0, 72);
}

GLuint EDS_Text::createTexture(const char* pText, GLfloat* scale)
{
	GLuint textureID;
	GLuint width, height, offset, offset_h, width_p2, height_p2;
	GLubyte* textureData;
	GLfloat scaleW, scaleH, ratio;
	std::vector<GLubyte*> charData;
	std::vector<GLuint> widths;
	std::vector<GLuint> heights;
	std::string text = pText;

	width = 0;
	height = 0;
	offset = 0;

	for (int i = 0; i < text.length(); i++)
	{
		GLuint tmp_width, tmp_height;
		charData.push_back(getChar(text[i], &tmp_width, &tmp_height, false));
		widths.push_back(tmp_width);
		heights.push_back(tmp_height);

		width += tmp_width;

		if (tmp_height > height)
		{
			height = tmp_height;
		}
	}

	if (width % 2 != 0) width += 1;
	if (height % 2 != 0) height += 1;

	height_p2 = 1;
	while (height_p2 < height) height_p2 <<= 1;
	scaleH = (GLfloat)height / (GLfloat)height_p2;
	offset_h = (height_p2 - height) / 2;
	height = height_p2;

	width_p2 = 1;
	while (width_p2 < width) width_p2 <<= 1;
	scaleW = (GLfloat)width / (GLfloat)width_p2;
	offset = (width_p2 - width) / 2;
	width = width_p2;

	ratio = (GLfloat)height / (GLfloat)width;

	if (scale != NULL)
	{
		//*scale = std::fmaxf(scaleH, scaleW);
		*scale = ratio;
	}

	//textureData = new GLubyte[width*height];
	textureData = new GLubyte[width * height];

	for (GLuint j = 0; j < offset; j++)
	{
		for (GLuint i = 0; i < height; i++)
		{
			textureData[i*width + j] = 0;
		}
	}

	for (GLuint k = 0; k < charData.size(); k++)
	{
		for (GLuint i = 0; i < height; i++)
		{
			for (GLuint j = 0; j < widths[k]; j++)
			{
				GLubyte byte;
				if ((i - offset_h) < heights[k] && i >= offset_h)
				{
					byte = charData[k][(i-offset_h)*widths[k] + j];
				}
				else
				{
					byte = 0;
				}

				textureData[i*width + j + offset] = byte;
			}
		}

		offset += widths[k];
	}

	for (GLuint j = offset; j < width; j++)
	{
		for (GLuint i = 0; i < height; i++)
		{
			textureData[i*width + j] = 0;
		}
	}

	textureID = TextureManager::loadBitmap(textureData, width, height, GL_ALPHA);

	return textureID;
}

GLubyte* EDS_Text::getChar(char c, GLuint* pWidth, GLuint* pHeight, bool makeEven)
{
	GLubyte* data;
	GLuint width, height, pitch;
	GLint offset;

	FT_Load_Char(fontInfo, c, FT_LOAD_RENDER);

	width = fontInfo->glyph->bitmap.width;
	height = fontInfo->glyph->bitmap.rows;
	pitch = fontInfo->glyph->bitmap.pitch;
	offset = fontInfo->glyph->bitmap_left;

	if ((width % 2 != 0) && makeEven)
	{
		width += 1;
	}

	data = (GLubyte*)malloc(sizeof(GLubyte) * width * height);

	for (GLuint i = 0; i < height; i++)
	{
		for (GLuint j = 0; j < pitch; j++)
		{
			data[i*width + j] = fontInfo->glyph->bitmap.buffer[(height - i - 1)*pitch + j];
		}
		for (GLuint j = pitch; j < width; j++)
		{
			data[i*width + j] = 0;
		}
	}

	*pWidth = width;
	*pHeight = height;

	return data;
}
