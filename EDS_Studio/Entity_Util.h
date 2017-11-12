
#ifndef ENTITY_UTIL_H
#define ENTITY_UTIL_H

#define ABS(x) ((x < 0) ? -x : x)

#define MOUSE_SCROLL_UP 3
#define MOUSE_SCROLL_DOWN 4

#define COORDINATE_RATIO 100.0f

#define SHADER_DIR				"shaders\\"
#define VERT_SHADER				".vert.shader"
#define FRAG_SHADER				".frag.shader"

#define TRANSPOSE_VERT_PATH		SHADER_DIR "transpose.vert.shader"
#define FILL_FRAG_PATH			SHADER_DIR "fill.frag.shader"
#define TEXTURE_FRAG_PATH		SHADER_DIR "texture.frag.shader"
#define TEXT_FRAG_PATH			SHADER_DIR "text.frag.shader"
#define BUTTON_FRAG_PATH		SHADER_DIR "button.frag.shader"

struct PointF
{
	float x;
	float y;
};

struct PointI
{
	int x;
	int y;
};

struct Rectangle
{
	struct PointF center;
	float angle;
	float width;
	float height;
};

struct Triangle
{
	struct PointI p1;
	struct PointI p2;
	struct PointI p3;
};

struct Color3f
{
	float r;
	float g;
	float b;
};

struct Color3i
{
	int r;
	int g;
	int b;
};


#endif //ENTITY_UTIL_H
