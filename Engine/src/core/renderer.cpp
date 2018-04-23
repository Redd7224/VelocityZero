#include "renderer.h"


Renderer::Renderer(Window& window) {
	createDevice(window);
	createRenderTarget();

}

void Renderer::createDevice(Window& window) {
	//Define swap chain. Used for buffering. 
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1; // 0 and 1
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //32 bit format for colors
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window.getHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = true; // TODO make this configurable

	//Create the swapchain device and device context
	auto result = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, //Feature level coudl down size to dx9 for example
		0,D3D11_SDK_VERSION,
		&swapChainDesc,	&m_pSwapChain, &m_pDevice,
		nullptr, //feature level again
		&m_pDeviceContext);

	//Example Error catch for a Direct X call
	if (result != S_OK) {
		MessageBox(nullptr, "Problem creating DX11", "ERROR", MB_OK);
		exit(0);
	}
}

void Renderer::createRenderTarget() {
	ID3D11Texture2D* backBuffer;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	m_pDevice->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView);
	backBuffer->GetDesc(&m_pBackBufferDesc);
	backBuffer->Release();
}


//Function mainly from tutorial. Will probbaly need to be rewroked. 
void Renderer::beginFrame() {
	// Bind render target
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

	//Set viewport determins what part of the screen to write to. may not need to be here?
	auto viewport = CD3D11_VIEWPORT(0.f, 0.f, (float)m_pBackBufferDesc.Width, (float)m_pBackBufferDesc.Height);
	m_pDeviceContext->RSSetViewports(1, &viewport);

	// Set the background color
	float backgroundColor[] = { .1f, .5f, .5f, 1 };
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, backgroundColor);
}

void Renderer::endFrame() {
	// Swap the buffer!
	m_pSwapChain->Present(1, 0);
}

ID3D11Device* Renderer::getDevice() {
	return m_pDevice;
}

ID3D11DeviceContext* Renderer::getDeviceContext() {
	return m_pDeviceContext;
}


