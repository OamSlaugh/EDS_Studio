
#include "EDS_Window.h"

EDS_Window::EDS_Window(char* name, int w, int h)
{
	ortho_scale = 1.0f;
	width = w;
	height = h;
	entities_l = LinkedList<EDS_Entity*>(10);
	glewInit();
}

EDS_Window::EDS_Window()
{
	EDS_Window("",300,300);
}

EDS_Window::~EDS_Window()
{

}

int EDS_Window::getWindowID()
{
	return window_id;
}

void EDS_Window::setWindowID(int id)
{
	window_id = id;
}

void EDS_Window::redraw()
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-ortho_scale*width / (2 * COORDINATE_RATIO), ortho_scale*width / (2 * COORDINATE_RATIO), -ortho_scale*height / (2 * COORDINATE_RATIO), ortho_scale*height / (2 * COORDINATE_RATIO));

	//glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < entities_l.count(); i++)
	{
		EDS_Entity* entity = *entities_l.itemAt(i);
		entity->draw();
	}

	glFlush();
	glutSwapBuffers();
}

struct PointF EDS_Window::convert_coord(int x, int y)
{
	PointF point;
	point.x = ortho_scale*(float)(x - width/2) / COORDINATE_RATIO;
	point.y = -ortho_scale*(float)(y - height/2) / COORDINATE_RATIO;
	return point;
}

void EDS_Window::mouse_click(int button, int state, int x, int y)
{
	mouse_pos = convert_coord(x, y);
	if (button == GLUT_LEFT_BUTTON)
	{
		active_entity = NULL;
		for (int i = entities_l.count()-1; i >= 0; i--)
		{
			bool inside;
			EDS_Entity* entity;
			entity = *entities_l.itemAt(i);
			inside = entity->checkBounds(mouse_pos);
			if (inside == true)
			{
				if (state == GLUT_DOWN)
				{
					active_entity = entity;
				}
				
				entities_l.moveToEnd(i);
				entity->mouseClick(button, state);
				break;
			}
		}
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (enable_zoom)
		{
			ortho_scale += 0.1f;
		}
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		if (enable_zoom)
		{
			if (ortho_scale > 0.2f)
			{
				ortho_scale -= 0.1f;
			}
		}
	}
	redraw();
}

void EDS_Window::mouse_move(int x, int y)
{
	if (active_entity != NULL)
	{
		if (active_entity->isMoveable())
		{
			if (active_entity->snap())
			{
				mouse_offset.x = 0.0f;
				mouse_offset.y = 0.0f;
			}
			else
			{
				mouse_offset.x = active_entity->getPos().x - mouse_pos.x;
				mouse_offset.y = active_entity->getPos().y - mouse_pos.y;
			}

			mouse_pos = convert_coord(x, y);
			active_entity->setPos(mouse_pos.x + mouse_offset.x, mouse_pos.y + mouse_offset.y);

			redraw();
		}
	}
}

void EDS_Window::passive_motion(int x, int y)
{
	bool redraw_required = false;
	struct PointF mouse_pos = convert_coord(x, y);

	/*for (int i = entities_l.count() - 1; i >= 0; i--)
	{
		redraw_required = (*entities_l.itemAt(i))->passiveMotion(mouse_pos);

		if (redraw_required)
		{
			break;
		}
	}*/
	
	redraw_required = (*entities_l.last())->passiveMotion(mouse_pos);

	if (redraw_required)
	{
		redraw();
	}
}

void EDS_Window::resize(int new_width, int new_height)
{
	width = new_width;
	height = new_height;

	redraw();
}

void EDS_Window::addEntity(EDS_Entity* toAdd)
{
	entities_l.push(toAdd);
}

int EDS_Window::getWidth()
{
	return width;
}

int EDS_Window::getHeight()
{
	return height;
}

