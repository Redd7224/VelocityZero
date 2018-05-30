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
std::map<int, ComPtr<ID3D11ShaderResourceView>> textureMap;
// keyboard and mouse are singletons. 
std::unique_ptr<DirectX::Keyboard> m_keyboard;
//std::unique_ptr<DirectX::Mouse> m_mouse;

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {
	int width = 800;
	int height = 600;
	//int width = 1280;
	//int height = 720;
	//int width = 1920;
	//int height = 1080;
	//int width = 2560;
	//int height = 1440;
	//int width = 3000;
	//int height = 2000;


	//Window window(1920, 1080);
	Window window(width, height);

	Renderer renderer(window, XMFLOAT2(width,height));
	MSG msg = { 0 }; //Window Message
	// TODO Create init function
	m_keyboard = std::make_unique<Keyboard>();
	//m_mouse = std::make_unique<Mouse>();
	//m_mouse->SetWindow(window.getHandle());
	
	// DXTOOLKIT
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(renderer.getDeviceContext());

	//TODO Make sure this timer works... Microsoft has it in most of their base app projects so I think we are good
	DX::StepTimer s_timer;
	//TODO decide if we want fixed update or not FIXED FPS
	s_timer.SetFixedTimeStep(true);
	s_timer.SetTargetElapsedSeconds(1.f / 60.f);
	//InputHandler* inputHander = new InputHandler(m_keyboard.get(),m_mouse.get());
	InputHandler* inputHander = new InputHandler(m_keyboard.get(), nullptr);
	// TODO add method to create textures?
	ComPtr<ID3D11ShaderResourceView> texture;
	
	CreateWICTextureFromFile(renderer.getDevice() , L"./art/PH_ground.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[1] = texture;
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/PH_wall.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[2] = texture;
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/0001-sheet.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[3] = texture;
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/LoadingScreen.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[4] = texture;
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/PH_ground_128_2.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[5] = texture;
	CreateWICTextureFromFile(renderer.getDevice(), L"./art/PH_Shop.png", nullptr, texture.ReleaseAndGetAddressOf());
	textureMap[6] = texture;
	Game game = Game(renderer.bufferResolution);
	
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

		//inputHander->Update();
		// Game Engine Update pass input get out things to draww
		s_timer.Tick([&]()
		{
			inputHander->Update();
			float delta = float(s_timer.GetElapsedSeconds());
			game.Update(delta, inputHander->m_pInputData);
		});
		
		//
		// Rendering Engine Update
		
		renderer.beginFrame();
		//User renderer to render things on frame
		m_spriteBatch->Begin();
		int lastTextureKey = 0;
		ID3D11ShaderResourceView* texture = nullptr;
		for (size_t i = 0; i < SPRITELAYERSCOUNT; i++)
		{
			for (size_t j = 0; j < game.spritesToDrawLayers[i].drawCount; j++)
			{
				SpriteInfo* currSprite = game.spritesToDrawLayers[i].spritesToDraw[j];
				if (currSprite->textureKey != -1) {
					if (lastTextureKey != currSprite->textureKey) {
						texture = textureMap[currSprite->textureKey].Get();
						lastTextureKey = currSprite->textureKey;
					}
					m_spriteBatch->Draw(texture, currSprite->position, &currSprite->sourceRect, Colors::White, currSprite->rotation, currSprite->origion, currSprite->scale, DirectX::SpriteEffects_None, 0.0f);
				}
			}
			
		}

		m_spriteBatch->End();


		//End rendering and display
		renderer.endFrame(); 
	}
	return 0;
}
