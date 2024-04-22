// graphic object for terrain 

#include "GraphicObject_Terrain.h"
#include "ShaderTextureLightFog.h"
#include "ShaderTexture.h"
#include "terrainModel.h"
#include "d3dUtil.h"
#include "Texture.h"

GraphicObject_Terrain::GraphicObject_Terrain(ShaderTextureLightFog* _shader, TerrainModel* _terrain)
{
	terrainModel = _terrain;
	myTexture = nullptr;
	myLightShader = _shader;
	world = Matrix(IDENTITY);
	shaderType = ShaderType::LIGHT_TEXTURE;
}

GraphicObject_Terrain::GraphicObject_Terrain(ShaderTexture* _shader, TerrainModel* _terrain)
{
	terrainModel = _terrain;
	myTexture = nullptr;
	myTexShader = _shader;
	world = Matrix(IDENTITY);
	shaderType = ShaderType::TEXTURE;
}

void GraphicObject_Terrain::SetWorld(const Matrix& m)
{
	world = m;
}

void GraphicObject_Terrain::SetTexture(Texture* tex)
{
	myTexture = tex;
}

void GraphicObject_Terrain::SetMaterialProperties(const Vect& _amb, const Vect& _dif, const Vect& _sp)
{
	amb = _amb;
	dif = _dif;
	sp = _sp;
}

void GraphicObject_Terrain::SetTerrainModel(TerrainModel* _terrainModel)
{
	terrainModel = _terrainModel;
}

void GraphicObject_Terrain::Render()
{
	assert(myTexture != nullptr);

	switch (shaderType)
	{
	case ShaderType::LIGHT_TEXTURE:

		myLightShader->SetTextureResourceAndSampler(myTexture);
		myLightShader->SendWorldAndMaterial(world, amb, dif, sp);
		terrainModel->Render(myLightShader->GetContext());

		break;

	case ShaderType::TEXTURE:

		myTexShader->SetTextureResourceAndSampler(myTexture);
		myTexShader->SendWorld(world);
		terrainModel->Render(myTexShader->GetContext());
		break;
	}


	
}