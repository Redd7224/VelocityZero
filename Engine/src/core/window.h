#pragma once
#include <Windows.h>
#include <Keyboard.h>
#include <Mouse.h>
class Window {
public: Window(int width, int height); 
		HWND getHandle();
private: HWND m_handle;
};