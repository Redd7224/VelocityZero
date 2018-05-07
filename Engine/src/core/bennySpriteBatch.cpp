#include <stdexcept>
#include <wrl\client.h>
#include "bennySpriteBatch.h"

using Microsoft::WRL::ComPtr;

BennySpriteBatch::BennySpriteBatch(ID3D11Device* device, ID3D11DeviceContext* deviceContext){
	m_pDevice = device;
	m_pDeviceContext = deviceContext;
	m_pVertices = new VertexPositionColorTexture[m_BatchSize * 4];
	CreateBuffers();
	CreateShaders();
	CreateBlendState();
}

BennySpriteBatch::~BennySpriteBatch(){}

void  BennySpriteBatch::CreateShaders() {
	// VertexShader load
	ID3D10Blob* _pVertexShader;
	ID3D10Blob* _pShaderError;

	if (S_OK != D3DX11CompileFromFile(
		TEXT("bennySpriteBatch.hlsl"), nullptr, nullptr, TEXT("SpriteVertexShader"),
		TEXT("vs_5_0"), 0, 0, nullptr, &_pVertexShader, &_pShaderError, nullptr))
	{
		MessageBox(0, (char*)_pShaderError->GetBufferPointer(),
			TEXT("Error im VShader"), 0);
		PostQuitMessage(1);
		return;
	}
	HRESULT hr1 = m_pDevice->CreateVertexShader(_pVertexShader->GetBufferPointer(),
		_pVertexShader->GetBufferSize(), nullptr, &m_pVertexShader);
	// PixelShader Load
	ID3D10Blob* _pPixelShader;

	if (S_OK != D3DX11CompileFromFile(
		TEXT("bennySpriteBatch.hlsl"), nullptr, nullptr, TEXT("SpritePixelShader"),
		TEXT("ps_5_0"), 0, 0, nullptr, &_pPixelShader, &_pShaderError, nullptr))
	{
		MessageBox(0, (char*)_pShaderError->GetBufferPointer(),
			TEXT("Error im PShader"), 0);
		PostQuitMessage(1);
		return;
	}
	m_pDevice->CreatePixelShader(_pPixelShader->GetBufferPointer(),
		_pPixelShader->GetBufferSize(), nullptr, &m_pPixelShader);

	D3D11_INPUT_ELEMENT_DESC _IED[] = {
		{ "SV_Position", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }, //SV_Position
		{ "COLOR",       0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	
	HRESULT hr = m_pDevice->CreateInputLayout(_IED, 3, _pVertexShader->GetBufferPointer(),
		_pVertexShader->GetBufferSize(), &m_pInputLayout);
	LPVOID p = _pVertexShader->GetBufferPointer();
	SIZE_T f = _pVertexShader->GetBufferSize();
	int x = 1;


}

void BennySpriteBatch::CreateBuffers() {
	// VertexBuffer Creae
	D3D11_BUFFER_DESC _VBufferDesc;
	ZeroMemory(&_VBufferDesc, sizeof(_VBufferDesc));

	_VBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	//_VBufferDesc.ByteWidth = BATCHSIZE * 4 * sizeof(VertexPositionColorTexture);
	_VBufferDesc.ByteWidth = m_BatchSize * 4 * sizeof(VertexPositionColorTexture);
	_VBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	_VBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	m_pDevice->CreateBuffer(&_VBufferDesc, nullptr, &m_pVertexBuffer);

	// IndexBuffer create
	D3D11_BUFFER_DESC _IBufferDesc;
	ZeroMemory(&_IBufferDesc, sizeof(_IBufferDesc));

	_IBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	//_IBufferDesc.ByteWidth = BATCHSIZE 6 * sizeof(unsigned int);
	_IBufferDesc.ByteWidth = m_BatchSize * 6 * sizeof(unsigned int);
	_IBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	_IBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	//I see some people crete Indicies here and set it to indexBufferDesc.pSysMem

	m_pDevice->CreateBuffer(&_IBufferDesc, nullptr, &m_pIndexBuffer);
	// No idea if these are right
	unsigned int _Indices[m_BatchSize * 6];

	for (size_t i = 0; i < m_BatchSize; i++)
	{
		_Indices[i * 6 + 0] = i * 4 + 0;
		_Indices[i * 6 + 1] = i * 4 + 1;
		_Indices[i * 6 + 2] = i * 4 + 2;
		_Indices[i * 6 + 3] = i * 4 + 0;
		_Indices[i * 6 + 4] = i * 4 + 2;
		_Indices[i * 6 + 5] = i * 4 + 3;
	}
	/*
	unsigned int _Indices[6];
	_Indices[0] = 0;
	_Indices[1] = 1;
	_Indices[2] = 2;
	_Indices[3] = 0;
	_Indices[4] = 2;
	_Indices[5] = 3;
	*/
	/*
	unsigned int _Indices[6];
	_Indices[0] = 0;
	_Indices[1] = 1;
	_Indices[2] = 2;
	_Indices[3] = 1;
	_Indices[4] = 3;
	_Indices[5] = 2;
	unsigned int _Indices[BATCHSIZE * 6];
	for (int x = 0; x < BATCHSIZE; x++)
	{
		_Indices[x * 6 + 0] = x * 4 + 0;
		_Indices[x * 6 + 1] = x * 4 + 1;
		_Indices[x * 6 + 2] = x * 4 + 2;
		_Indices[x * 6 + 3] = x * 4 + 0;
		_Indices[x * 6 + 4] = x * 4 + 2;
		_Indices[x * 6 + 5] = x * 4 + 3;
	}
	*/
	//D3D11_SUBRESOURCE_DATA indexDataDesc = {};

	//indexDataDesc.pSysMem = _Indices;
	
	D3D11_MAPPED_SUBRESOURCE _MSR;

	m_pDeviceContext->Map(m_pIndexBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &_MSR);
	//memcpy(_MSR.pData, _Indices, BATCHSIZE * 6 * sizeof(unsigned int));
	memcpy(_MSR.pData, _Indices, m_BatchSize * 6 * sizeof(unsigned int));
	m_pDeviceContext->Unmap(m_pIndexBuffer, 0);
}

void BennySpriteBatch::CreateBlendState() {
	D3D11_BLEND_DESC _BDesc;
	ZeroMemory(&_BDesc, sizeof(_BDesc));

	_BDesc.AlphaToCoverageEnable = false;
	_BDesc.IndependentBlendEnable = false;

	_BDesc.RenderTarget[0].BlendEnable = true;
	_BDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	_BDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	_BDesc.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	_BDesc.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;


	_BDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	_BDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	_BDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

	m_pDevice->CreateBlendState(&_BDesc, &m_pBlendState);
}
void BennySpriteBatch::Begin() {
	m_DrawCallCount = 0;
}
void BennySpriteBatch::End() {

	D3D11_MAPPED_SUBRESOURCE _MSR;

	m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &_MSR);
	memcpy(_MSR.pData, m_pVertices, m_BatchSize * 4 * sizeof(VertexPositionColorTexture));
	m_pDeviceContext->Unmap(m_pVertexBuffer, 0);


	// States setzen
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pCurrentTexture);

	m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, 0xFFFFFFFF);

	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);
	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);

	UINT _Stride = sizeof(VertexPositionColorTexture);
	UINT _Offset = 0;
	m_pDeviceContext->IASetInputLayout(m_pInputLayout);
	m_pDeviceContext->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0); //DXGI_FORMAT_R16_UINT  ???
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &_Stride, &_Offset);

	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// DrawCall
	//Can probably make this smarter
	m_pDeviceContext->DrawIndexed(m_DrawCallCount * 6, 0, 0);
}

void BennySpriteBatch::Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position) {
	Draw(p_pTexture, position, XMFLOAT4(0, 1, 0, 1));
}

void BennySpriteBatch::Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, float scale) {
	Draw(p_pTexture, position, XMFLOAT4(0, 1, 0, 1), scale);
}

void BennySpriteBatch::Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source, float scale) {
	Draw(p_pTexture, position, source, XMFLOAT4(1, 1, 1, 1), scale);
}

void BennySpriteBatch::Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source) {
	Draw(p_pTexture, position, source, XMFLOAT4(1, 1, 1, 1), 1.0f);
}


void BennySpriteBatch::Draw(ID3D11ShaderResourceView* p_pTexture, XMFLOAT2 position, XMFLOAT4 source, XMFLOAT4 color, float scale) {
	//This is lazy batching? flushing when texture changes.
	if (m_pCurrentTexture != p_pTexture) {
		End();
		Begin();
		m_pCurrentTexture = p_pTexture;
	}
	//TODO there should be some logic for size? if source is defined?
	XMVECTOR texture_size = GetTextureSize(p_pTexture);
	texture_size *= scale;
	//TODO get screensize
	//XMVectorGetX(texture_size); is expensive may want to store current texutre size in member variable. 
	//or add vectors together
	float _PosXStart = position.x / 800 * 2 - 1;
	float _PosXEnd = (position.x + XMVectorGetX(texture_size)) / 800 * 2 - 1;
	float _PosYStart = -1 * (position.y / 600 * 2 - 1);
	float _PosYEnd = -1 * ((position.y + XMVectorGetY(texture_size)) / 600 * 2 - 1);

	m_pVertices[m_DrawCallCount * 4 + 0].position = XMFLOAT3(_PosXStart, _PosYEnd, 0);
	m_pVertices[m_DrawCallCount * 4 + 1].position = XMFLOAT3(_PosXStart, _PosYStart, 0);
	m_pVertices[m_DrawCallCount * 4 + 2].position = XMFLOAT3(_PosXEnd, _PosYStart, 0);
	m_pVertices[m_DrawCallCount * 4 + 3].position = XMFLOAT3(_PosXEnd, _PosYEnd, 0);
	
	m_pVertices[m_DrawCallCount * 4 + 0].color = color;
	m_pVertices[m_DrawCallCount * 4 + 1].color = color;
	m_pVertices[m_DrawCallCount * 4 + 2].color = color;
	m_pVertices[m_DrawCallCount * 4 + 3].color = color;

	//TODO calculate source from pixel positions and texture size?
	//set texture corods
	m_pVertices[m_DrawCallCount * 4 + 0].textureCoordinate = XMFLOAT2(source.x, source.z);
	m_pVertices[m_DrawCallCount * 4 + 1].textureCoordinate = XMFLOAT2(source.x, source.w);
	m_pVertices[m_DrawCallCount * 4 + 2].textureCoordinate = XMFLOAT2(source.y, source.w);
	m_pVertices[m_DrawCallCount * 4 + 3].textureCoordinate = XMFLOAT2(source.y, source.z);
	
	m_DrawCallCount++;

	if (m_DrawCallCount >= m_BatchSize)
	{
		End();
		Begin();
	}
}



XMVECTOR BennySpriteBatch::GetTextureSize(ID3D11ShaderResourceView* texture)
{
	// Convert resource view to underlying resource.
	ComPtr<ID3D11Resource> resource;

	texture->GetResource(&resource);

	// Cast to texture.
	ComPtr<ID3D11Texture2D> texture2D;

	if (FAILED(resource.As(&texture2D)))
	{
		throw std::exception("SpriteBatch can only draw Texture2D resources");
	}

	// Query the texture size.
	D3D11_TEXTURE2D_DESC desc;

	texture2D->GetDesc(&desc);

	// Convert to vector format.
	XMVECTOR size = XMVectorMergeXY(XMLoadInt(&desc.Width),
		XMLoadInt(&desc.Height));

	return XMConvertVectorUIntToFloat(size, 0);
}
