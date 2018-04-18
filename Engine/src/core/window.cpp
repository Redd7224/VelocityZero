#include <Windows.h>
#include "window.h"

// handle is window specific handler; msg is event message bring processed. wparam and lparam are event arguments.
// Can or will be used to handle user input
LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam) {
	//Handle Window Destory or Close
	if (msg == WM_DESTROY || msg == WM_CLOSE) {
		PostQuitMessage(0);  // Windows handler to Quit application?
		return 0;
	}
	
	//Default event handling.
	return DefWindowProc(handle,msg,wparam,lparam); 
}


Window::Window(int width, int height){

	//Define custom Window Style. Will be used to draw DX?
	WNDCLASS wc = { 0 }; // init all members to zero
	wc.style = CS_OWNDC; // Style? I beleive hardware device for use in DX
	wc.lpfnWndProc = WinProc; //Window Procedure. Function used to process events from the window. 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); //define cursor. Can be removed at somepoint to draw custom cursor in DX
	wc.lpszClassName = "VelocityZero"; //Windows Style class name
	RegisterClass(&wc); //Register the Class so it can be found by Create Window


	//Creates Window
	CreateWindow("VelocityZero", //Name of Window Style class. Using Custom class
		"Velocity Zero", //Window title
		WS_POPUP | WS_CAPTION | WS_SYSMENU |WS_VISIBLE, //Window Styles. WS_POPUP = window mode? WS_CAPTION = title bar; WS_SYSMENU = close button?
		100, 100, width, height, //Default position and size
		nullptr, nullptr, nullptr, nullptr);
}