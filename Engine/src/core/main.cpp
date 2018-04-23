#include <Windows.h>
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "triangle.h"

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	Window window(800, 600);
	Renderer renderer(window);
	MSG msg = { 0 }; //Window Message

	//Create Temp Triangle class
	Triangle triangle(renderer);

	

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
		renderer.beginFrame();
		//User renderer to render things on frame
		triangle.draw(renderer);
		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}