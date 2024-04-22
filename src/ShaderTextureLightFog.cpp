// class for shader texture with light and fog

#include "ShaderTextureLightFog.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>
#include "Texture.h"

ShaderTextureLightFog::ShaderTextureLightFog(ID3D11Device* device)
	:ShaderBase(device, L"../Assets/Shaders/TextureLightFog.hlsl")
{

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
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

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&PointLightData2, sizeof(PointLightData));
	ZeroMemory(&PointLightData3, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));

	// fog param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Fog_Parameters);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferFogParams);
	assert(SUCCEEDED(hr));

	// set default fog

	this->SetFogParameters(DefaultFogStart, DefaultFogRange, DefaultFogColor);
}

void ShaderTextureLightFog::SetToContext(ID3D11DeviceContext* devcon)
{

	this->SetContext(devcon);
	this->SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWordAndMaterial);
	devcon->VSSetConstantBuffers(2, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(3, 1, &mpBufferFogParams);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBuffWordAndMaterial);
	devcon->PSSetConstantBuffers(2, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(3, 1, &mpBufferFogParams);
}

void ShaderTextureLightFog::SetTextureResourceAndSampler(Texture* tex)
{
	currentTexture = tex;
	currentTexture->SetToContext(this->GetContext());
}

void ShaderTextureLightFog::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTextureLightFog::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

void ShaderTextureLightFog::SetPointLightParameters(int lightNum, const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{


	switch (lightNum)
	{
	case 1:

		PointLightData.Light.Ambient = amb;
		PointLightData.Light.Diffuse = dif;
		PointLightData.Light.Specular = sp;
		PointLightData.Position = pos;
		PointLightData.Attenuation = att;
		PointLightData.Range = r;

		break;

	case 2:

		PointLightData2.Light.Ambient = amb;
		PointLightData2.Light.Diffuse = dif;
		PointLightData2.Light.Specular = sp;
		PointLightData2.Position = pos;
		PointLightData2.Attenuation = att;
		PointLightData2.Range = r;

		break;

	case 3:

		PointLightData3.Light.Ambient = amb;
		PointLightData3.Light.Diffuse = dif;
		PointLightData3.Light.Specular = sp;
		PointLightData3.Position = pos;
		PointLightData3.Attenuation = att;
		PointLightData3.Range = r;

		break;
	}
}

void ShaderTextureLightFog::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData.Light.Ambient = amb;
	SpotLightData.Light.Diffuse = dif;
	SpotLightData.Light.Specular = sp;
	SpotLightData.Position = pos;
	SpotLightData.Direction = dir;
	SpotLightData.Attenuation = att;
	SpotLightData.Range = r;
	SpotLightData.SpotExp = spotExp;
}

void ShaderTextureLightFog::SetFogParameters(float _FogStart, float _FogRange, Vect _FogColor)
{
	fogParams.FogStart = _FogStart;
	fogParams.FogRange = _FogRange;
	fogParams.FogColor = _FogColor;
}

void ShaderTextureLightFog::SendFogParameters()
{
	Fog_Parameters fp;
	fp = fogParams;

	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &fp, 0, 0);
}

void ShaderTextureLightFog::SendLightParameters(const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	dl.PntLight = PointLightData;
	dl.PntLight2 = PointLightData2;
	dl.PntLight3 = PointLightData3;
	dl.SptLight = SpotLightData;
	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderTextureLightFog::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

ShaderTextureLightFog::~ShaderTextureLightFog()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBufferFogParams);
}