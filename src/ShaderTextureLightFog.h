// class for shader texture with light and fog 

#ifndef _ShaderTextureLightFog
#define _ShaderTextureLightFog

#include "ShaderBase.h"
class Texture;
#include "Matrix.h"
#include "d3dUtil.h"
#include <d3d11.h>

class ShaderTextureLightFog : public ShaderBase
{
public:

	// varify these params 
	const float DefaultFogStart = 2000.0f;
	const float DefaultFogRange = 1.0f;
	const Vect DefaultFogColor = Vect(1.0f, 1.0f, 1.0f);

	ShaderTextureLightFog(ID3D11Device* device);
	~ShaderTextureLightFog();

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(int lightnum, const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetFogParameters(float FogStart, float FogRange, Vect FogColor); // add defaults for no fog here 

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetTextureResourceAndSampler(Texture* tex);
	void SendLightParameters(const Vect& eyepos);
	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFogParameters();

private:

	Texture* currentTexture;

	// --------------- light stuff

	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData;
	PointLight PointLightData2;
	PointLight PointLightData3;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData;

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer* mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer* mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		PointLight PntLight2;
		PointLight PntLight3;
		SpotLight SptLight;
		Vect EyePosWorld;
	};

	ID3D11Buffer* mpBufferLightParams;

	struct Fog_Parameters
	{
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	Fog_Parameters fogParams;

	ID3D11Buffer* mpBufferFogParams;

};



#endif _ShaderTextureLightFog
