
#include "WindowManager.h"
#include "LinkedList.h"

EDS_Window gWindow;
LinkedList<EDS_Window> gWindows_l;

bool WindowManager::first = true;

void WindowManager::initialize(int* pArgc, char** argv)
{
	glutInit(pArgc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(500, 500);
	gWindows_l = LinkedList<EDS_Window>(10);
	WindowManager::first = true;
}

EDS_Window* WindowManager::createWindow(char* name, int width, int height)
{
	EDS_Window new_wnd;
	int wndID;
	new_wnd = EDS_Window(name,width,height);


	wndID = glutCreateWindow(name);
	new_wnd.setWindowID(wndID);

	//if (WindowManager::first == true)
	{
		
		glutDisplayFunc(WindowManager::redrawWindows);
		glutMouseFunc(WindowManager::mouseClickCallback);
		glutMotionFunc(WindowManager::mouseMoveCallback);
		glutReshapeFunc(WindowManager::resizeCallback);
		glutPassiveMotionFunc(WindowManager::passiveMotionCallback);

		WindowManager::first = false;
	}


	gWindows_l.push(new_wnd);
	return gWindows_l.last();
}

void WindowManager::redrawWindows()
{
	/*EDS_Window* wnd;
	wnd = activeWindow();

	if (wnd != NULL)
	{
		wnd->redraw();
	}*/

	for (int i = 0; i < gWindows_l.count(); i++)
	{
		EDS_Window* wnd;
		wnd = gWindows_l.itemAt(i);
		glutSetWindow(wnd->getWindowID());
		wnd->redraw();

	}
}

void WindowManager::mouseClickCallback(int button, int state, int x, int y)
{
	activeWindow()->mouse_click(button, state, x, y);
}

void WindowManager::mouseMoveCallback(int x, int y)
{
	activeWindow()->mouse_move(x, y);
}

void WindowManager::passiveMotionCallback(int x, int y)
{
	activeWindow()->passive_motion(x, y);
}

void WindowManager::resizeCallback(int width, int height)
{
	activeWindow()->resize(width, height);
}

EDS_Window* WindowManager::activeWindow()
{
	int wndID = 0;
	EDS_Window* wnd = NULL;
	wndID = glutGetWindow();

	gWindows_l.pointer(0);
	for (int i = 0; i < gWindows_l.count(); i++)
	{
		wnd = gWindows_l.next();
		if (wnd->getWindowID() == wndID)
		{
			break;
		}
		else
		{
			wnd = NULL;
		}
	}

	return wnd;
}

void WindowManager::run()
{
	glutMainLoop();
}
