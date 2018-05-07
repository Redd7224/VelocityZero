#include <Windows.h>
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "triangle.h"
#include "SpriteBatch.h"
#include "bennySpriteBatch.h"


int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	Window window(800, 600);
	Renderer renderer(window);
	MSG msg = { 0 }; //Window Message

	//Create Temp Triangle class
	Triangle triangle(renderer);

	ID3D11ShaderResourceView* m_pTexture;
	
	SpriteBatch sp;
	sp.Init(renderer.getDevice(), renderer.getDeviceContext());

	BennySpriteBatch bsb(renderer.getDevice(), renderer.getDeviceContext());
	//Dirt.jpg
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
		bsb.Begin();
		bsb.Draw(m_pTexture, XMFLOAT2(200, 200),.1f);
		bsb.Draw(m_pTexture, XMFLOAT2(400, 500),.1f);
		bsb.End();

		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}