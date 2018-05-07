#pragma once
#include <d3d11.h>
#include <D3DX11.h>
#include <DirectXMath.h>
#include "bennyVertexPosColTex.h"

class BennySpriteBatch {
public:
	BennySpriteBatch(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~BennySpriteBatch();
	void Begin();
	void End();
	void Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position);
	void Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, float scale);
	void Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source);
	void Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source, float scale);
	void Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source, XMFLOAT4 color, float scale);
private:
	void CreateBuffers();
	void CreateShaders();
	void CreateBlendState();
	XMVECTOR GetTextureSize(ID3D11ShaderResourceView* texture);

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;

	ID3D11InputLayout* m_pInputLayout;
	ID3D11BlendState* m_pBlendState;

	// May Be Better way to do this then have membervairable
	ID3D11ShaderResourceView* m_pCurrentTexture;
	VertexPositionColorTexture* m_pVertices;
	int m_DrawCallCount;

	float m_ScreenWidth;
	float m_ScreenHeight;

	static const size_t m_BatchSize = 2048;

};