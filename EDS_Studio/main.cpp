
#include <GL\glew.h>
#include <GL\freeglut.h>

#include "WindowManager.h"
#include "TextureManager.h"
#include "EDS_Button.h"
GLuint vertBuffID;

void click_event()
{
	int i = 0;
	i = i + 1;
}

int main(int argc, char** argv)
{
	vertBuffID = 1;

	EDS_Window* wnd;
	EDS_Window* wnd2;
	WindowManager::initialize(&argc, argv);
	
	glewInit();
	
	TextureManager::initialize();
	wnd = WindowManager::createWindow("EDS Studio", 300, 300);
	wnd2 = WindowManager::createWindow("Window 2", 300, 300);

	EDS_Entity square;
	square = EDS_Entity();
	
	EDS_Button button = EDS_Button(60, 20, "Button");
	button.setReleaseEvent(click_event);
	wnd->addEntity(&button);
	//size = sizeof(EDS_Button);
	//wnd->addEntity(&square);
	square.setPos(0.25f, 0.25f);

	WindowManager::run();
	TextureManager::close();
	return 0;
}