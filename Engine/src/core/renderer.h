#pragma once
#include "window.h"
#include <d3d11.h>

class Renderer {
public:
	Renderer(Window& window);
	void beginFrame();
	void endFrame();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();

private:
	void createDevice(Window& window);
	void createRenderTarget();


	// Device stuff

	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr; //Device that will be used to render

	// Render target
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_pBackBufferDesc;
};
