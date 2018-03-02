#pragma once

#include <windows.h>
#include <string>
#include <iostream>

class CConsole
{
public:
	void setup()
	{
		AllocConsole();
		HWND hw = GetConsoleWindow();
		MoveWindow(hw, 70, 210, 500, 600, 1);
		EnableMenuItem(GetSystemMenu(hw, 0), SC_CLOSE, MF_DISABLED);
		SetConsoleTitleA("DemoNames");
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
	}
	void destroy()
	{
		system("cls");
		EnableMenuItem(GetSystemMenu(GetConsoleWindow(), 0), SC_CLOSE, MF_ENABLED);
		std::cout << "can close me now";
		FreeConsole();
	}
} console;