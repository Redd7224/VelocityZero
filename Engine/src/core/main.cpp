#include <Windows.h>
#include "main.h"
#include "window.h"

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {

	Window window(800, 600);

	MSG msg = { 0 }; //Window Message
	while (true) {
		//Handle Program Exit
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) { break; }
		}

		// Main loop
		// 
		// Game Engine Update
		// Rendering Engine Update
	}
	return 0;
}