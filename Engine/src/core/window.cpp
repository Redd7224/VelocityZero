#include "window.h"

// handle is window specific handler; msg is event message bring processed. wparam and lparam are event arguments.
// Can or will be used to handle user input
LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg)
	{

	case WM_CLOSE:
	case WM_DESTROY:
			PostQuitMessage(0);  // Windows handler to Quit application?
			return 0;
			break;
	
	case WM_ACTIVATEAPP:
		DirectX::Keyboard::ProcessMessage(msg, wparam, lparam);
		//DirectX::Mouse::ProcessMessage(msg, wparam, lparam);
		break;
/*
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		DirectX::Mouse::ProcessMessage(msg, wparam, lparam);
		break;
		*/
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		DirectX::Keyboard::ProcessMessage(msg, wparam, lparam);
		break;
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


	//Figure out client size adjuestmnet. need to have this smart enough for full screen as well?
	RECT windowRect;
	SetRect(&windowRect, 0, 0, width, height);
	AdjustWindowRect(&windowRect, WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, false);


	//Creates Window
	m_handle = CreateWindow("VelocityZero", //Name of Window Style class. Using Custom class
		"Velocity Zero", //Window title
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, //Window Styles. WS_POPUP = window mode? WS_CAPTION = title bar; WS_SYSMENU = close button? 
		100, 100, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, //Default position and size //windowRect.right - windowRect.left, windowRect.bottom - windowRect.top // width, height
		nullptr, nullptr, nullptr, nullptr);
	RECT clientRect;
	GetClientRect(m_handle, &clientRect);
	int x = 1;
}

HWND Window::getHandle()
{
	return m_handle;
}