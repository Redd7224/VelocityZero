#include <Windows.h>
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "triangle.h"
#include "SpriteBatch.h"
int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	Window window(800, 600);
	Renderer renderer(window);
	MSG msg = { 0 }; //Window Message

	//Create Temp Triangle class
	Triangle triangle(renderer);

	ID3D11ShaderResourceView* m_pTexture;
	SpriteBatch sp;
	sp.Init(renderer.getDevice(), renderer.getDeviceContext());
	D3DX11CreateShaderResourceViewFromFile(renderer.getDevice(), TEXT("Dirt.jpg"),
		nullptr, nullptr, &m_pTexture, nullptr);

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
		//triangle.draw(renderer);
		sp.Begin();
		sp.DrawTexture(m_pTexture, Rect(100, 100, 100, 100), Rect(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR4(1, 1, 1, 1));
		sp.DrawTexture(m_pTexture, Rect(400, 400, 100, 100), Rect(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR4(1, 1, 1, 1));
		sp.DrawTexture(m_pTexture, Rect(150, 150, 100, 100), Rect(0.5f, 0.5f, 0.5f, 0.5f), D3DXVECTOR4(1, 1, 1, 1));
		sp.End();

		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}