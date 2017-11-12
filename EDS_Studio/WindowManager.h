
#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "EDS_Window.h"
#include <list>

class WindowManager
{
public:
	static void initialize(int* pArgc, char** argv);
	static void addWindow(EDS_Window wnd);
	static EDS_Window* createWindow(char* name, int width, int height);
	static void run();
private:
	static void redrawWindows();
	static void mouseClickCallback(int button, int state, int x, int y);
	static void mouseMoveCallback(int x, int y);
	static void passiveMotionCallback(int x, int y);
	static void resizeCallback(int width, int height);
	static EDS_Window* activeWindow();
	static bool WindowManager::first;
};

#endif //WINDOW_MANAGER_H
