#pragma once
#include "window.h"
#include <d3d11.h>
#include <DirectXMath.h>


class Renderer {
public:
	Renderer(Window& window, DirectX::XMFLOAT2 resolution);
	void beginFrame();
	void endFrame();
	ID3D11Device* getDevice();
	ID3D11DeviceContext* getDeviceContext();
	DirectX::XMFLOAT2 bufferResolution = DirectX::XMFLOAT2(0, 0);
private:
	void createDevice(Window& window);
	void createRenderTarget();
	void setBufferResolution(DirectX::XMFLOAT2 resolution);

	// Device stuff

	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr; //Device that will be used to render

	// Render target
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	D3D11_TEXTURE2D_DESC m_pBackBufferDesc;


	//Default buffer sizes for aspect ratios
	DirectX::XMFLOAT2 m_default_buffer_43 = DirectX::XMFLOAT2(800, 600);
	DirectX::XMFLOAT2 m_default_buffer_32 = DirectX::XMFLOAT2(1200, 800);
	DirectX::XMFLOAT2 m_default_buffer_1610 = DirectX::XMFLOAT2(1280, 800);
	DirectX::XMFLOAT2 m_default_buffer_169 = DirectX::XMFLOAT2(1280, 720);

};
