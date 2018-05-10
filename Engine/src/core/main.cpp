#include <Windows.h>
#include "main.h"
#include "window.h"
#include "renderer.h"
#include "pch.h"
#include "game.h"
#include "spriteInfo.h"
#include "inputHandler.h"
#include "inputData.h"
#include "StepTimer.h"
#include <wrl\client.h>
#include <DirectXHelpers.h>
#include <SpriteBatch.h>
#include <map>
#include <string>

using Microsoft::WRL::ComPtr;
using namespace DirectX;

//These vairables probably dont belong here
//Map may not be as quick as just passing around and holding onto pointers
std::map<std::string, ComPtr<ID3D11ShaderResourceView>> textureMap;
// keyboard and mouse are singletons. 
std::unique_ptr<DirectX::Keyboard> m_keyboard;
std::unique_ptr<DirectX::Mouse> m_mouse;

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	Window window(800, 600);
	Renderer renderer(window);
	MSG msg = { 0 }; //Window Message
	// TODO Create init function
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window.getHandle());
	
	// DXTOOLKIT
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(renderer.getDeviceContext());

	//TODO Make sure this timer works... Microsoft has it in most of their base app projects so I think we are good
	DX::StepTimer s_timer;
	
	InputHandler* inputHander = new InputHandler(m_keyboard.get(),m_mouse.get());

	// TODO add method to create textures?
	ComPtr<ID3D11ShaderResourceView> texture;
	
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/PH_ground.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap["PH_ground.png"] = texture;
	Game game = Game(XMFLOAT2(800,600));
	
	int x = 0;
	int y = 0;
	while (true) {
		// Handle Program Exit
		auto kb = m_keyboard.get()->GetState();
		if (kb.Escape) {
			break;
		}
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) { break; }
		}

		// Main loop
		// Get Input
		//	
		// Game Engine Update pass input get out things to draww
		s_timer.Tick([&]()
		{
			float delta = float(s_timer.GetElapsedSeconds());
			inputHander->Update();
			game.Update(delta, inputHander->m_pInputData);
		});
		
		//
		// Rendering Engine Update
		
		renderer.beginFrame();
		//User renderer to render things on frame
		m_spriteBatch->Begin();
		for (auto &spriteInfo : game.m_spritesToDraw) // access by reference to avoid copying
		{
			m_spriteBatch->Draw(textureMap[spriteInfo.textureName].Get(), spriteInfo.position, nullptr, Colors::White, spriteInfo.rotation, XMFLOAT2(0, 0));
		}
		m_spriteBatch->End();


		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}