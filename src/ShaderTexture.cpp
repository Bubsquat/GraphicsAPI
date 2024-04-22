// class for shader texture

#include "ShaderTexture.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Texture.h"

ShaderTexture::ShaderTexture(ID3D11Device* device)
	:ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// World buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WorldMatrix);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWord);
	assert(SUCCEEDED(hr));

}

void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon)
{

	this->SetContext(devcon);
	this->SetToContext_VS_PS_InputLayout();
	//currentTexture->SetToContext(devcon);
	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWord);

}

void ShaderTexture::SetTextureResourceAndSampler(Texture* tex)
{
	currentTexture = tex;
	currentTexture->SetToContext(this->GetContext());
}

void ShaderTexture::SendCamMatrices(const Matrix& view, const Matrix& proj)
{

	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTexture::SendWorld(const Matrix& world)
{

	WorldMatrix W;
	W.World = world;

	this->GetContext()->UpdateSubresource(mpBuffWord, 0, nullptr, &W, 0, 0);

}

ShaderTexture::~ShaderTexture()
{
	ReleaseAndDeleteCOMobject(mpBuffWord);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}