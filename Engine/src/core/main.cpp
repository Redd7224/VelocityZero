#include <Windows.h>
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "pch.h"
#include "game.h"
#include <wrl\client.h>
#include <DirectXHelpers.h>
#include <SpriteBatch.h>



using Microsoft::WRL::ComPtr;
using namespace DirectX;
int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	Window window(800, 600);
	Renderer renderer(window);
	MSG msg = { 0 }; //Window Message
	// TODO Create init function
	// DXTOOLKIT
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(renderer.getDeviceContext());


	// TODO add method to create textures?
	ComPtr<ID3D11ShaderResourceView> m_texture;
	
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/PH_ground.png", nullptr,m_texture.ReleaseAndGetAddressOf());
	Game game = Game();
	
	int x = 0;
	int y = 0;
	while (true) {
		// Handle Program Exit
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) { break; }
		}

		// Main loop
		// Get Input
		//	
		// Game Engine Update pass input get out things to draww
		game.Update();
		//
		// Rendering Engine Update
		
		renderer.beginFrame();
		//User renderer to render things on frame
		m_spriteBatch->Begin();
		m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(100, 100), nullptr, Colors::White, 0.0f,  XMFLOAT2(0,0));

		m_spriteBatch->End();


		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}