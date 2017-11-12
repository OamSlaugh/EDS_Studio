#ifndef EDS_WINDOW_H
#define EDS_WINDOW_H

#include <GL\glew.h>
#include <GL\freeglut.h>
#include "EDS_Entity.h"
#include "EDS_Button.h"
#include "LinkedList.h"

class EDS_Window
{
public:
	EDS_Window();
	EDS_Window(char* name, int w, int h);
	~EDS_Window();

	int getWindowID();
	void setWindowID(int id);
	int getWidth();
	int getHeight();
	void addEntity(EDS_Entity* toAdd);
	void mouse_click(int button, int state, int x, int y);
	void mouse_move(int x, int y);
	void passive_motion(int x, int y);
	void resize(int new_width, int new_height);
	void redraw();
	
private:
	struct PointF convert_coord(int x, int y);

	int window_id;
	int width;
	int height;
	float ortho_scale;
	bool enable_zoom;
	struct PointF mouse_pos;
	struct PointF mouse_offset;
	EDS_Entity* active_entity;
	LinkedList<EDS_Entity*> entities_l;
	LinkedList<EDS_Button> buttons_l;
};

//typedef void(EDS_Entity::*mouse_click)(int button, int state, int x, int y);


#endif //EDS_STUDIO_H
