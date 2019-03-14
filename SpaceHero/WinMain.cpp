#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "Constants.h"
#include "resource.h"
#include "Director.h"
#include "SpaceHero.h"

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam);
bool CreateMainWindow(HWND &, HINSTANCE, int);
bool AnotherInstance();


int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE, PWSTR CommandLine, int ShowCode)
{
	// Check if appliaction already started
	if (AnotherInstance())
		return 0;
	
	// Create the application's window
	HWND Window = NULL;
	if (!CreateMainWindow(Window, Instance, ShowCode))
	{
		MessageBox(NULL, L"Unable to create window", L"Error", MB_OK);
		return 0;
	}		

	// Start up game engine
	Engine::Director* director = Engine::Director::getInstance();
	SpaceHero* game = new SpaceHero;
	try
	{
		RECT lpRect{};
		GetClientRect(Window, &lpRect);
		director->StartUp(Window, lpRect.right - lpRect.left, lpRect.bottom - lpRect.top);
		
		game->Init();
	}
	catch (int errorcode)
	{
		// TODO(Marko): Write Error class
		MessageBox(NULL, L"Error", L"Error", MB_OK);
		return 0;
	}

	// Enter the message loop
	MSG message = {};

	while (game->IsRunning())
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			// Look for quit message
			if (message.message == WM_QUIT)
				game->GameOver();
			// Decode and pass messages on to WinProc
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
			game->UpdateAndDraw();			
	}

	delete game;

	// Shut down the game engine
	director->ShutDown();

	return 0;
}

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (Message)
	{
	   case WM_DESTROY:
	   {
		   PostQuitMessage(0);
	   } break;
	   case WM_CHAR:
	   {
		   if (wParam == VK_ESCAPE)
			   PostQuitMessage(0);
	   } break;
	   default:
		   result = DefWindowProc(Window, Message, wParam, lParam);
	}
	return result;
}

bool CreateMainWindow(HWND &windowHandle, HINSTANCE Instance, int ShowCode)
{
	// Register the window class
	WNDCLASS windowsClass = {};

	windowsClass.lpfnWndProc = WindowProc;
	windowsClass.hInstance = Instance;
	windowsClass.lpszClassName = CLASS_NAME;
	windowsClass.hCursor = LoadCursor(NULL, IDC_ARROW);   // predefined arrow 
	windowsClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowsClass.hIcon = LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON1));

	RegisterClass(&windowsClass);

	// Create the window.
	windowHandle = CreateWindowEx(
		0,                          // Optional window styles.
		CLASS_NAME,                 // Window class
		GAME_TITLE,                 // Window text
		WS_CAPTION | WS_SYSMENU,    // Window style

						   // Size and position
		CW_USEDEFAULT,     // Horizontal position
		CW_USEDEFAULT,     // Vertical position
		GAME_WIDTH,        // Window width
		GAME_HEIGHT,       // Window height

		NULL,              // Parent window    
		NULL,              // Menu
		Instance,          // Instance handle
		NULL               // Additional application data
	);

	if (windowHandle == NULL)
		return 0;

	// Show the window
	ShowWindow(windowHandle, ShowCode);

	// Send a WM_PAINT message to the window procedure
	UpdateWindow(windowHandle);
	return true;
}

bool AnotherInstance()
{
	HANDLE appMutex;
	// Attempt to create a mutex using our unique string
	appMutex = CreateMutex(NULL, true, L"spaceHeroMutex");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return true; 
	return false;
}