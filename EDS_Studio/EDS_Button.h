
#ifndef EDS_BUTTON_H
#define EDS_BUTTON_H

#include "EDS_Entity.h"

class EDS_Button : public EDS_Entity
{
public:
	EDS_Button();
	EDS_Button(int width, int height, const char* pText);
	~EDS_Button();
	void draw();
	void mouseClick(int button, int state);
	bool passiveMotion(struct PointF mouse_pos);

	void setPressEvent(void(*callback)());
	void setReleaseEvent(void(*callback)());
	bool isPressed();

private:
	void initButton();
	void updateColor(Color3i _color, bool update = true);
	Color3i colorPressed;
	Color3i colorReleased;
	Color3i colorHover;
	Color3i textColor;
	std::string text;
	GLint colorBuff;
	bool newColor;

protected:
	bool pressed;
	void(*onPress)();
	void(*onRelease)();
};

#endif //EDS_BUTTON_H
